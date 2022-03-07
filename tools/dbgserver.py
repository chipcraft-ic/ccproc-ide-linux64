#!/usr/bin/env python2
# -*- coding: utf-8 -*-

#
# Copyright (c) 2017 ChipCraft Sp. z o.o.
#
# GDB compatible Debug Server for CC Processor
#
# Author: Rafal Harabien
#
# $Date: 2021-06-24 15:44:21 +0200 (czw, 24 cze 2021) $
# $Revision: 711 $
#

import time, sys, os, stat, select, threading, logging, re, struct, binascii, socket, serial, getopt, signal

is_py2 = sys.version[0] == '2'
if is_py2:
    import Queue as queue
else:
    import queue as queue

# Default options
GDB_PORT = 3333
DBG_PORT = '/dev/ttyUSB1'
DBG_BAUDRATE = 460800

# Constants
DEBUG_BREAKPOINTS = 0x90000000
DEBUG_WATCHPOINTS = 0x90000010
DEBUG_BURST_COUNT = 0x90000020
DEBUG_REGS = 0x91000000
MAX_BURST_LEN = 0xFFC
BREAKPOINTS_NUM = 4
WATCHPOINTS_NUM = 4
ACK_CHR = b'\6'
SIGINT = 2
SIGTRAP = 5
BREAK_OPCODE = b'\x00\x00\x03\xCD'
MEM_REGION_ALIGNMENT = 0x10000


class DebuggerDisconnectedException(Exception):
    """Raised when GDB debugger disconnects from debug server."""
    pass

class DebuggerInterruptedException(Exception):
    """Raised when GDB debugger sends interrupt byte (0x03) to stop program execution."""
    pass

class TargetDisconnectedException(Exception):
    """Raised when target hardware is disconnected."""
    pass

class GdbConn:
	"""Represents connection with GDB client. Uses socket for communication.
	Supports sending and parsing packets in GDB Remote Protocol."""

	def __init__(self, sock, cpu_input_thread):
		self._sock = sock
		self._buf = b''
		self._buf_offset = 0
		self._packet_queue = queue.Queue()
		self._cpu_input_thread = cpu_input_thread
		self._no_ack_mode = False
		self._input_thread = threading.Thread(target=self._input_thread_proc, name='GDB Input')
		self._input_thread.daemon = True
		self._input_thread.start()

	def get_packet(self, timeout=None):
		while True:
			data = self._get_from_queue(timeout)
			if data not in [b'+', b'-']:
				return data
			logging.warn('Expected GDB packet, got ACK (%s)', data)

	def _get_from_queue(self, timeout=None):
		if not self._packet_queue:
			# Got EOF before
			logging.debug('Got EOF from GDB before')
			return None
		try:
			data = self._packet_queue.get(timeout != 0, timeout)
			if not data:
				logging.debug('Got EOF from GDB')
				self._packet_queue = None
				self._input_thread = None
			return data
		except queue.Empty:
			logging.debug('Timeout when reading GDB input queue (%s)', timeout)
			return None

	def send_packet(self, data):
		packet = self._prepare_packet(data)

		while True:
			logging.debug('Sending GDB packet: %s', packet)
			self._write(packet)
			if self._no_ack_mode:
				return True
			ack = self._get_from_queue(timeout=5)
			if not ack:
				logging.warning('Failed to read ACK from GDB')
				return False
			elif ack == b'+':
				logging.debug('Received ACK from GDB')
				return True
			else:
				logging.warning('Expected ACK from GDB, got \'%s\' (%s) (packet %s)', ack, binascii.hexlify(ack), packet)

	def _input_thread_proc(self):
		try:
			while True:
				data = self._read_packet()
				if data == b'\3':
					self._cpu_input_thread.put_interrupt()
				else:
					self._packet_queue.put(data)
				if not data:
					self._cpu_input_thread.put_exit_flag()
				if not data or data == b'D':
					logging.debug('Ending GDB input thread')
					self._packet_queue = None
					break
		except:
			logging.exception('Uncaught exception')

	def _read_byte(self):
		if self._buf_offset == len(self._buf):
			self._buf = self._read()
			self._buf_offset = 0
		if self._buf:
			self._buf_offset = self._buf_offset + 1
			return self._buf[self._buf_offset - 1:self._buf_offset]

	def _read_packet(self):
		in_packet = False

		while True:
			ch = self._read_byte()
			if not ch:
				# EOF
				logging.debug('Got EOF from GDB in _read_packet')
				return None

			if ch == b'$':
				data = b''
				checksum = 0
				in_packet = True
			elif not in_packet:
				if ch in [b'\3', b'+', b'-']:
					# Interrupt, ACK, NACK
					logging.debug('Got special byte %s from GDB', ch)
					return ch
				else:
					logging.warn('Ignoring non-packet byte %s', ch)
			elif ch == b'#':
				ch1 = self._read_byte()
				ch2 = self._read_byte()
				if not ch1 or not ch2:
					logging.error('Failed to read packet checksum')
					return None

				xmitcsum = int(ch1 + ch2, 16)
				checksum = checksum % 256
				if checksum == xmitcsum:
					break # success
				else:
					logging.warning('Invalid checksum (0x%X != 0x%X)', checksum, xmitcsum)
					self._write(b'-')
					in_packet = False
			else:
				data = data + ch
				checksum += ord(ch)

		# send ACK
		if not self._no_ack_mode:
			self._write(b'+')

		# unescape binary data and return
		escape_pattern = re.compile(b'\x7D(.)', flags=re.DOTALL)
		data = escape_pattern.sub(lambda m: bytes(bytearray((ord(m.group(1)) ^ 0x20,))), data)
		return data

	def _prepare_packet(self, data):
		checksum = 0
		for b in data:
			checksum += ord(b) if is_py2 else b
		checksum = checksum % 256
		return b'$' + data + b'#' + ('%02X' % checksum).encode('ascii')

	def _read(self):
		if self._sock:
			return self._sock.recv(1024)
		elif hasattr(sys.stdin, 'buffer'):
			return sys.stdin.buffer.read(1)
		else:
			return sys.stdin.read(1)

	def _write(self, data):
		if self._sock:
			self._sock.send(data)
		elif hasattr(sys.stdout, 'buffer'):
			sys.stdout.buffer.write(data)
			sys.stdout.flush()
		else:
			sys.stdout.write(data)
			sys.stdout.flush()
	
	def start_no_ack_mode(self):
		self._no_ack_mode = True


class StreamLoggingWrapper:
	"""Serial Port proxy with logging support."""

	def __init__(self, inner, log_path=None):
		self._inner = inner
		self._log_path = log_path
		self._log_file = None
		if self._log_path:
			self._log_file = open(self._log_path, 'wb')

	def write(self, data):
		if logging.getLogger().isEnabledFor(logging.DEBUG): # dont hexlify if not needed
			logging.debug('Serial Write: %s %s', binascii.hexlify(data).decode('ascii'), binascii.b2a_qp(data))
		if self._log_file:
			self._log_file.write(data + b'\n')
		return self._inner.write(data)

	def read(self, size=1):
		data = self._inner.read(size)
		if logging.getLogger().isEnabledFor(logging.DEBUG): # dont hexlify if not needed
			logging.debug('Serial Read: %s %s', binascii.hexlify(data).decode('ascii'), binascii.b2a_qp(data))
		return data

	def close(self):
		self._inner.close()
		if self._log_file:
			self._log_file.close()
			self._log_file = None


class CpuInputThread(threading.Thread):
	def __init__(self, serial):
		threading.Thread.__init__(self)
		self._serial = serial
		self._queue = queue.Queue()
		self.closing = False
		self._debugger_disconnected_flag = False
		self._interrupted_flag = False
		self._target_disconnected_flag = False

	def run(self):
		try:
			while True:
				if self.closing:
					logging.debug('Close request in CpuInputThread - exiting')
					break
				try:
					data = self._serial.read()
				except serial.SerialException as e:
					if not self.closing:
						logging.error('Serial exception: %s', e)
					else:
						logging.debug('Ending CPU input thread after port close')
					break
				if data:
					self._queue.put(data)
				else:
					logging.debug('Ending CPU input thread - read returned 0')
					break
			
			self._target_disconnected_flag = True
			self._queue.put('')

		except:
			logging.exception('Uncaught exception')

	def get_byte(self, timeout=None, interruptible=False):
		try:
			if interruptible:
				self._check_flags()
			data = self._queue.get(timeout != 0, timeout)
			if not data and interruptible:
				self._check_flags()
			return data
		except queue.Empty:
			logging.debug('Timeout when reading CPU queue (%s)', timeout)
			return None

	def put_interrupt(self):
		logging.debug('Adding interrupt flag to CPU queue')
		self._interrupted_flag = True
		self._queue.put('')

	def put_exit_flag(self):
		logging.debug('Adding exit flag to CPU queue')
		self._debugger_disconnected_flag = True
		self._queue.put('')

	def _check_flags(self):
		if self._debugger_disconnected_flag:
			self._debugger_disconnected_flag = False
			raise DebuggerDisconnectedException()
		if self._interrupted_flag:
			self._interrupted_flag = False
			raise DebuggerInterruptedException()
		if self._target_disconnected_flag:
			self._target_disconnected_flag = False
			raise TargetDisconnectedException()


class CpuDebug:
	"""Communication with Processor Debugger through Serial Port."""

	def __init__(self, serial, mcu_name=None):
		self._serial = serial
		#self._serial.close()
		self._cur_addr = None
		self._auto_inc = None
		self._core_ctx = {}
		self._core_id = None
		self._cores_num = None
		self._mcu_name = mcu_name
		self._input_thread = None
		self._burst_len = 0
		self._burst_started = False

		self._create_input_thread()

	def get_input_thread(self):
		return self._input_thread

	def _create_input_thread(self):
		self._input_thread = CpuInputThread(self._serial)
		self._input_thread.name = 'CPU Input'
		self._input_thread.daemon = True
		self._input_thread.start()

	def _read(self, size=1, timeout=5, interruptible=False):
		result = b''
		for i in range(0, size):
			byte = self._input_thread and self._input_thread.get_byte(timeout, interruptible)
			if byte == b'':
				logging.debug('Got interrupt from CPU input queue')
				if i == 0 and interruptible:
					return b''
				else:
					logging.warn('Ignoring unexpected interrupt from CPU input queue')
					byte = self._input_thread and self._input_thread.get_byte(timeout, interruptible)
					if byte == b'':
						logging.warn('Got second unexpected interrupt from CPU input queue')
			result += byte or b''
		logging.debug('Read from CPU input queue: %s %s', binascii.hexlify(result).decode('ascii'), binascii.b2a_qp(result))
		return result

	def _write(self, data):
		self._serial.write(data)

	def expect_ack(self):
		ack = self._read()
		if ack != ACK_CHR:
			logging.warning('Expected ACK from CPU, got \'%s\' (0x%X)', binascii.b2a_qp(ack), ord(ack or b'\0'))
			return False
		return True

	def set_addr(self, addr):
		if addr == self._cur_addr:
			# already there
			logging.debug('set_addr optimized out')
			return True

		assert addr % 4 == 0
		self._write(b'a' + struct.pack('>I', addr))
		success = self.expect_ack()
		if success:
			self._cur_addr = addr
		else:
			self._cur_addr = None
		return success

	def _inc_addr_after_rw(self):
		if self._auto_inc:
			self._cur_addr += 4
		elif self._auto_inc is None:
			self._cur_addr = None

	def read_mem_word(self):
		if not self._burst_started:
			self._write(b'm')
			if self._burst_len > 0:
				self._burst_started = True

		if self._burst_len > 0:
			self._burst_len -= 4
			if self._burst_len == 0:
				self._burst_started = False
				logging.debug('Burst finished')

		res = self._read(4)
		if len(res) != 4:
			logging.warning('read_mem failed')
			self._cur_addr = None
			return None
		self._inc_addr_after_rw()
		return res

	def write_mem_word(self, word):
		assert len(word) == 4
		if not self._burst_started:
			self._write(b'w')
			if self._burst_len > 0:
				self._burst_started = True

		self._write(word)

		if self._burst_len > 0:
			self._burst_len -= 4
			if self._burst_len == 0:
				self._burst_started = False
				logging.debug('Burst finished')

		if self._burst_len == 0:
			success = self.expect_ack()
			if not success:
				logging.warning('write_mem failed')
				self._cur_addr = None
				return False

		self._inc_addr_after_rw()
		return True

	def _read_mem_aligned(self, addr, length):
		if length > 4 and not self.set_auto_inc(True):
			return None
		data = b''
		for offset in range(0, length, 4):
			self._setup_burst_mode(addr + offset, length - offset)
			if not self.set_addr(addr + offset):
				return None
			word = self.read_mem_word()
			if not word:
				return None

			data += word

		return data

	def read_mem(self, addr, length):
		start_misalignment = addr % 4
		start_aligned = addr - start_misalignment
		end_misalignment = (addr + length) % 4
		end_aligned = (addr + length) + (4 - end_misalignment) % 4
		data = self._read_mem_aligned(start_aligned, end_aligned - start_aligned)
		if data:
			data = data[start_misalignment:]
			data = data[:length]
		return data

	def _write_mem_aligned(self, addr, data):
		if len(data) > 4 and not self.set_auto_inc(True):
			return False
		for offset in range(0, len(data), 4):
			self._setup_burst_mode(addr + offset, len(data) - offset)
			if not self.set_addr(addr + offset):
				return False
			if not self.write_mem_word(data[offset:offset+4]):
				return False
		return True

	def write_mem(self, addr, data):
		# Fix start address misalignment
		start_misalign = addr % 4
		start_word = None
		addr -= start_misalign
		if not self.set_addr(addr):
			return False
		if start_misalign != 0:
			if not self.set_auto_inc(False):
				return False
			start_word = self.read_mem_word()
			if not start_word:
				return False
			data = start_word[:start_misalign] + data
		# Aligned write
		assert addr % 4 == 0
		end_misalign = len(data) % 4
		aligned_len = len(data) - end_misalign
		if not self._write_mem_aligned(addr, data[:aligned_len]):
			return False
		# Fix end address misalignment
		if end_misalign != 0:
			end_word_addr = addr + len(data) - end_misalign
			assert end_word_addr % 4 == 0
			if not self.set_addr(end_word_addr):
				return False
			if end_word_addr != addr or not start_word:
				if not self.set_auto_inc(False):
					return False
				end_word = self.read_mem_word()
				if not end_word:
					return False
				if not self.set_auto_inc(True):
					return False
			else:
				end_word = start_word
			data += end_word[end_misalign:]
			new_end_word = data[aligned_len:]
			assert len(new_end_word) == 4
			if not self.write_mem_word(new_end_word):
				return False
		return True

	def set_auto_inc(self, enabled):
		if enabled == self._auto_inc:
			# this autoinc mode is already selected - skip
			return True
		if enabled:
			self._write(b'I')
		else:
			self._write(b'i')
		got_ack = self.expect_ack()
		if got_ack:
			self._auto_inc = enabled
		else:
			self._auto_inc = None
		return got_ack

	def set_core(self, core_id):
		if core_id == self._core_id:
			# this core is already selected - skip
			return True
		self._write(struct.pack('>B', 160+core_id))
		got_ack = self.expect_ack()
		if got_ack:
			self._core_id = core_id
		else:
			self._core_id = None
		return got_ack

	def get_core(self):
		return self._core_id

	def free_run(self):
		self._write(b'f')
		return self.expect_ack()

	def step(self):
		self._write(b's')

	def break_cpu(self):
		self._write(b'b')

	def reset_cpu(self):
		#self.write_mem(0x30030028, '\0\0\0\1') # remap
		self._write(b'r')
		return self.expect_ack()

	def reset_debugger(self):
		self._write(b'R')
		return self.expect_ack()

	def read_reg(self, idx):
		return self.read_mem(DEBUG_REGS + idx*4, 4)

	def read_regs(self):
		return self.read_mem(DEBUG_REGS, 32*4)

	def write_regs(self, data):
		return self.write_mem(DEBUG_REGS, data)

	def get_pc_reg(self):
		ctx = self._core_ctx[self._core_id]
		if ctx:
			return ctx['addr']

		logging.error('PC address is unknown')
		return None

	def is_core_active(self, core_id):
		if core_id in self._core_ctx and self._core_ctx[core_id]:
			return True
		return False

	def get_active_cores(self):
		return [core_id for core_id in self._core_ctx if self._core_ctx[core_id]]

	def get_core_ctx(self, core_id):
		if core_id in self._core_ctx:
			return self._core_ctx[core_id]
		return None

	def set_breakpoint(self, idx, addr):
		addr_bin = struct.pack('>I', addr)
		return self.write_mem(DEBUG_BREAKPOINTS + idx*4, addr_bin)

	def get_breakpoint(self, idx):
		addr_bin = self.read_mem(DEBUG_BREAKPOINTS + idx*4, 4)
		if not addr_bin:
			return None
		addr, = struct.unpack('>I', addr_bin)
		return addr

	def set_watchpoint(self, idx, addr):
		addr_bin = struct.pack('>I', addr)
		return self.write_mem(DEBUG_WATCHPOINTS + idx*4, addr_bin)

	def get_watchpoint(self, idx):
		addr_bin = self.read_mem(DEBUG_WATCHPOINTS + idx*4, 4)
		if not addr_bin:
			return None
		addr, = struct.unpack('>I', addr_bin)
		return addr

	def _read_core_context(self):
		core_id_raw = self._read()
		core_id = ord(core_id_raw)
		is_working = (core_id & 0x80) == 0
		core_id &= 0x7F
		if is_working:
			ctx = {}
			addr_bin = self._read(4)
			addr, = struct.unpack('>I', addr_bin)
			ctx['addr'] = addr

			instr = self._read(4)
			instr_str = binascii.hexlify(instr)
			ctx['instr'] = instr

			result, = struct.unpack('>I', self._read(4))
			data, = struct.unpack('>I', self._read(4))
			lsaddr, = struct.unpack('>I', self._read(4))
			ldata, = struct.unpack('>I', self._read(4))
			ctx['lsaddr'] = lsaddr

			if instr_str[0:4] == b'dead':
				logging.warning('Core %d is executing 16-bit instruction at 0x%X: %s', core_id, addr, instr_str[4:])
			else:
				logging.info('Core %d is executing instruction at 0x%X: %s', core_id, addr, instr_str)
				logging.info('  result 0x%X data 0x%X lsaddr 0x%X ldata 0x%X', result, data, lsaddr, ldata)
		else:
			ctx = None
			logging.info('Core %d is halted', core_id)

		return core_id, ctx

	def wait_for_context(self, timeout=None, first_ch=None, interruptible=False):
		idx = 0
		max_core_id = -1

		while not self._cores_num or idx < self._cores_num:
			# Read first character
			if first_ch:
				ch = first_ch
				first_ch = None
			else:
				ch = self._read(timeout=timeout, interruptible=interruptible)

			if not ch:
				# Timeout or interrupt
				if idx > 0:
					if not self._cores_num:
						# Timeout was expected - now we know number of cores
						self._cores_num = max_core_id + 1
						logging.info('Number of cores: %d', self._cores_num)
						break
					else:
						logging.warning('Timeout when reading context')
				else:
					logging.debug('Timeout when waiting for context')

				return False

			if ch != b'~':
				logging.warning('Expected \'~\' from CPU, got \'%s\' (0x%X)', binascii.b2a_qp(ch), ord(ch or b'\0'))
				continue

			core_id, ctx = self._read_core_context()
			self._core_ctx[core_id] = ctx
			max_core_id = max(max_core_id, core_id)
			idx += 1
			# Change timeout for next cores
			timeout = 0.1
			interruptible = False

		return True

	def break_for_context(self):
		# check if there is any data available
		logging.debug('Checking if context was already sent')
		if self.wait_for_context(0.1):
			logging.debug('Got context before sending break')
			return

		# check if processor is running
		logging.debug('Checking processor state')
		self._write(b'B')
		ch = self._read(timeout=1)

		if not ch:
			# fallback to old method if 'B' is not supported
			self._write(b's')
			ch = self._read(timeout=1)

		if ch == ACK_CHR or not ch:
			# ACK after 'B' or timeout after 's' - processor is running
			logging.debug('Processor is running - halting')
			self._write(b'b')
			ch = None
		logging.debug('Processor is halted - read context data')
		self.wait_for_context(None, ch)

	def _setup_burst_mode(self, addr, length):
		# Burst mode makes sense only if auto-increment is enabled
		if not self._auto_inc:
			return
		# Check if burst mode is already active
		if self._burst_len != 0:
			return
		# Calculate actual burst length and check if it is bigger than one word
		next_reg_addr = addr - addr % MEM_REGION_ALIGNMENT + MEM_REGION_ALIGNMENT
		burst_len = min(length, MAX_BURST_LEN, next_reg_addr - addr)
		if burst_len <= 4:
			return
		# Seek to burst count register
		burst_len_bin = struct.pack('>I', burst_len)
		self.set_addr(DEBUG_BURST_COUNT)
		# Write burst length into the register
		self.write_mem_word(burst_len_bin)
		# Remember burst length for later - it will be decremented when reading/writing words
		self._burst_len = burst_len
		# Burst is considered started after first command (e.g. 'm') is sent to the debug chip
		self._burst_started = False
		logging.debug('Enabled burst mode (addr 0x%X, length %d)', addr, burst_len)

class DbgBridge:
	"""Handles GDB Remote Protocol commands and convert them to CC Processor Debugger commands."""

	def __init__(self, gdb_conn, cpu_dbg):
		self._gdb_conn = gdb_conn
		self._cpu_dbg = cpu_dbg
		self._breakpoints = [None] * BREAKPOINTS_NUM
		self._watchpoints = [None] * WATCHPOINTS_NUM
		# use SIGTRAP by default; GDB expects it after 'step' command
		self._sig = SIGTRAP
		self._gdb_sync = False

	def cmd_read_regs(self):
		logging.info('Reading registers...')
		gregs = self._cpu_dbg.read_regs()
		pc = self._cpu_dbg.get_pc_reg() or 0
		status = self._cpu_dbg.read_mem(0x3003000, 4)
		#epc = self._cpu_dbg.read_mem(0x3003004, 4) # current PC is more useful
		cause = self._cpu_dbg.read_mem(0x3003008, 4)
		badaddr = self._cpu_dbg.read_mem(0x300300C, 4)

		if not gregs or not status or not cause or not badaddr:
			logging.error('Failed to read registers')
			return b'E01'

		regs_hex = b''
		regs_hex += binascii.hexlify(gregs)
		regs_hex += binascii.hexlify(status)
		regs_hex += b'00000000' * 2 # lo, hi
		regs_hex += binascii.hexlify(badaddr)
		regs_hex += binascii.hexlify(cause)
		regs_hex += '{0:08X}'.format(pc).encode('ascii')
		regs_hex += b'00000000' * 32 # floating point registers
		regs_hex += b'00000000' * 2 # fsr, fir registers

		return regs_hex

	def cmd_write_regs(self, arg):
		regs = binascii.unhexlify(arg)

		gregs = regs[:32*4]
		pc_bin = regs[(32+5)*4:(32+6)*4]
		pc, = struct.unpack('>I', pc_bin)

		if pc == 0:
			# GDB wants to restart program - reset processor
			logging.info('Resetting processor...')
			self._cpu_dbg.reset_cpu()
			self._cpu_dbg.break_cpu()
			self._cpu_dbg.wait_for_context()
			return b'OK'
		else:
			logging.info('Writing registers...')
			# Note: pc cannot be changed in processor yet
			if self._cpu_dbg.write_regs(gregs):
				return b'OK'
			else:
				logging.error('Failed to write registers')
				return b'E01'

	def cmd_read_mem(self, arg):
		i = arg.index(b',')
		addr = int(arg[:i], 16)
		length = int(arg[i+1:], 16)
		if length == 0:
			return ''

		data = self._cpu_dbg.read_mem(addr, length)
		if not data:
			return b'E01'
		data_hex = binascii.hexlify(data)
		logging.info('Read %d bytes from 0x%08X: %s', length, addr, data_hex)
		return data_hex

	def cmd_write_mem(self, arg):
		i = arg.index(b',')
		j = arg.index(b':')
		addr = int(arg[:i], 16)
		length = int(arg[i+1:j], 16)
		data_hex = arg[j+1:]
		data = binascii.unhexlify(data_hex)
		if length == 0:
			return ''

		if len(data) != length:
			logging.error('Invalid length field in write_mem command')

		logging.info('Wrote %d bytes at 0x%08X: %s', length, addr, data_hex)
		if self._cpu_dbg.write_mem(addr, data):
			return b'OK'
		else:
			return b'E01'

	def cmd_write_mem_bin(self, arg):
		i = arg.index(b',')
		j = arg.index(b':')
		addr = int(arg[:i], 16)
		length = int(arg[i+1:j], 16)
		data = arg[j+1:]

		if len(data) != length:
			logging.error('Invalid length field in write_mem_bin command %d %d', len(data), length)

		logging.info('Writing %d bytes at 0x%08X: %s', len(data), addr, binascii.hexlify(data))
		if self._cpu_dbg.write_mem(addr, data):
			if len(data) > 1024:
				logging.info('Writing operation finished!')
			return b'OK'
		else:
			return b'E01'

	def cmd_insert_breakpoint(self, arg):
		args = arg.split(b',')
		t = args[0]
		addr = int(args[1], 16)
		length = int(args[2], 16)
		logging.info('Inserting breakpoint: type %s addr 0x%08X len %d', t, addr, length)

		found = False
		success = False

		if t in [b'0', b'1']: # software/hardware breakpoint
			for i in range(0, BREAKPOINTS_NUM):
				if self._breakpoints[i] is None:
					found = True
					success = self._cpu_dbg.set_breakpoint(i, addr)
					if success:
						self._breakpoints[i] = addr
					break
		elif t in [b'2', b'3', b'4']: # watchpoint (write, read, access)
			for i in range(0, WATCHPOINTS_NUM):
				if self._watchpoints[i] is None:
					found = True
					success = self._cpu_dbg.set_watchpoint(i, addr)
					if success:
						self._watchpoints[i] = addr
					break
		else:
			logging.error('Unsupported breakpoint type %s!', t)
			return ''

		if success:
			return b'OK'
		elif not found:
			logging.warning('Empty slot for breakpoint not found')
		else:
			logging.error('Failed to set breakpoint')
		return b'E01'

	def cmd_remove_breakpoint(self, arg):
		args = arg.split(b',')
		t = args[0]
		addr = int(args[1], 16)
		length = int(args[2], 16)
		logging.info('Removing breakpoint: type %s addr 0x%08X len %d', t, addr, length)

		found = False
		success = False

		if t in [b'0', b'1']: # software/hardware breakpoint
			for i in range(0, BREAKPOINTS_NUM):
				if self._breakpoints[i] == addr:
					found = True
					success = self._cpu_dbg.set_breakpoint(i, 0xFFFFFFFF)
					if success:
						self._breakpoints[i] = None
					break
		elif t in [b'2', b'3', b'4']: # watchpoint (write, read, access)
			for i in range(0, WATCHPOINTS_NUM):
				if self._watchpoints[i] == addr:
					found = True
					success = self._cpu_dbg.set_watchpoint(i, 0xFFFFFFFF)
					if success:
						self._watchpoints[i] = None
					break
		else:
			logging.error('Unsupported breakpoint type %s!', t)
			return b''

		if success:
			return b'OK'
		elif not found:
			logging.error('Breakpoint not found')
		else:
			logging.error('Failed to remove breakpoint')
		return b'E01'

	def cmd_continue(self, arg):
		if len(arg) != 0:
			logging.warning('Ignoring continue address!')

		logging.info('Continue...')
		self._cpu_dbg.free_run()

	def cmd_step(self, arg):
		if len(arg) != 0:
			logging.warning('Ignoring step address!')

		logging.info('Step')
		self._cpu_dbg.step()

	def cmd_detach(self):
		logging.info('GDB detached.')
		self._cpu_dbg.free_run()
		return b'OK'

	def cmd_remote_command(self, arg):
		cmd = binascii.unhexlify(arg)
		logging.info('Remote command: %s', cmd)
		if cmd == b'reset halt':
			old_bp = self._cpu_dbg.get_breakpoint(0)
			# Stop as early as possible (address 0)
			self._cpu_dbg.set_breakpoint(0, 0)
			self._cpu_dbg.reset_cpu()
			self._cpu_dbg.break_cpu()
			self._cpu_dbg.wait_for_context()
			self._cpu_dbg.set_breakpoint(0, old_bp if old_bp else 0xFFFFFFFF)
			self.select_best_core()
			return b'OK'
		elif cmd == b'reset run':
			self._cpu_dbg.reset_cpu()
			return b'OK'
		elif cmd.startswith(b'delay '):
			ms = int(cmd[6:])
			time.sleep(ms / 1000)
			return b'OK'
		elif cmd == b'halt':
			self._cpu_dbg.break_cpu()
			self._cpu_dbg.wait_for_context()
			self.select_best_core()
			return b'OK'
		elif cmd.startswith(b'core '):
			core_id = int(cmd[5:])
			logging.info('Changing core to %d', core_id)
			self._cpu_dbg.set_core(core_id)
			return b'OK'
		elif cmd == b'gdb_sync':
			# Fake next stepi command so it does not step but return current address
			# This is useful to sync GDB state after monitor halt command
			self._gdb_sync = True
			return b'OK'
		logging.warn('Unknown command: %s', cmd)
		return b''

	def get_exception_info(self):
		# Note: T packet allows GDB for not reading all registers
		repl = 'T{0:02X}'.format(self._sig)

		# GDP frequently needs SP, FP, RA and PC registers
		logging.debug('Reading registers...')
		for idx in [29, 30, 31]:
			reg_bin = self._cpu_dbg.read_reg(idx)
			reg, = struct.unpack('>I', reg_bin)
			repl += '{0:02X}:{1:08X};'.format(idx, reg)

		pc = self._cpu_dbg.get_pc_reg() or 0
		repl += '{0:02X}:{1:08X};'.format(37, pc) # PC
		repl += 'thread:{0:08X};'.format(self._cpu_dbg.get_core() + 1) # current core
		return repl.encode('ascii')

	def find_best_core(self, hint):
		best_core_id = hint

		# check if any core is halted on breakpoint
		for core_id in self._cpu_dbg.get_active_cores():
			ctx = self._cpu_dbg.get_core_ctx(core_id)
			if not ctx:
				continue
			if ctx['instr'] == BREAK_OPCODE:
				best_core_id = core_id
				logging.debug('Break instruction detected!')
			elif ctx['addr'] in self._breakpoints:
				best_core_id = core_id
				logging.debug('Halted on hw breakpoint!')
			elif not self._cpu_dbg.is_core_active(best_core_id):
				# if current core is halted, switch to first active
				best_core_id = core_id

		# if no core is running, use 0
		if not self._cpu_dbg.is_core_active(best_core_id):
			best_core_id = 0

		return best_core_id

	def select_best_core(self):
		best_core_id = self.find_best_core(self._cpu_dbg.get_core())
		if best_core_id != self._cpu_dbg.get_core():
			logging.info('Selecting best core %d', best_core_id)
			self._cpu_dbg.set_core(best_core_id)

	def setup_debugger(self):
		if not self._setup_done:
			# Initial setup
			logging.info('Initializing debugger')
			self._cpu_dbg.set_auto_inc(True)

			# Setup breakpoints and watchpoints to address which cannot be accessed
			# Note: reset_debugger() is not used because it unbreaks processor
			for i in range(0, BREAKPOINTS_NUM):
				self._cpu_dbg.set_breakpoint(i, 0xFFFFFFFF)
			for i in range(0, WATCHPOINTS_NUM):
				self._cpu_dbg.set_watchpoint(i, 0xFFFFFFFF)

			# Select core
			best_core_id = self.find_best_core(0)
			self._cpu_dbg.set_core(best_core_id)

			self._setup_done = True
			logging.debug('Initialized.')

	def handle_gdb_packet(self, data):
		logging.debug('Handling GDB packet: %s', data)
		repl = b''
		exit = False
		cmd = data[0:1]
		arg = data[1:]

		if cmd == b'?': # last exception number
			self._cpu_dbg.break_for_context()
			self.setup_debugger()
			repl = self.get_exception_info()
		elif cmd == b'c': # cAA..AA: Continue at address AA..AA(optional)
			self.cmd_continue(arg)
			self.wait_for_exception()
			repl = self.get_exception_info()
		elif cmd == b's': # Step one instruction from AA..AA(optional)
			if self._gdb_sync:
				self._gdb_sync = False
			else:
				self.cmd_step(arg)
				self.wait_for_exception()
			repl = self.get_exception_info()
		elif cmd == b'g': # return the value of the CPU registers
			repl = self.cmd_read_regs()
		elif cmd == b'G': # set the value of the CPU registers - return OK
			repl = self.cmd_write_regs(arg)
		elif cmd == b'm': # mAA..AA,LLLL: Read LLLL bytes at address AA..AA
			repl = self.cmd_read_mem(arg)
		elif cmd == b'M': # MAA..AA,LLLL: Write LLLL bytes at address AA.AA return OK
			repl = self.cmd_write_mem(arg)
		elif cmd == b'X': # XAA..AA,LLLL: Write LLLL bytes at address AA.AA return OK
			repl = self.cmd_write_mem_bin(arg)
		elif cmd == b'Z': # insert breakpoint
			repl = self.cmd_insert_breakpoint(arg)
		elif cmd == b'z': # remove breakpoint
			repl = self.cmd_remove_breakpoint(arg)
		elif cmd == b'D': # detach
			repl = self.cmd_detach()
			exit = True
		elif cmd == b'q':
			args = re.split(b'[,:]', arg)
			if args[0] == b'Rcmd': # monitor command
				repl = self.cmd_remote_command(args[1])
			elif args[0] == b'Supported':
				repl = b'PacketSize=1400;QStartNoAckMode+'
			elif args[0] == b'Offsets':
				repl = b'Text=0;Data=0;Bss=0'
			elif args[0] == b'C': # current thread
				# Note: GDB thread IDs starts from 1
				core_id = self._cpu_dbg.get_core()
				repl = b'QC{0}'.format(core_id + 1)
			elif args[0] == b'Symbol':
				repl = b'OK' # no symbol is needed
			elif args[0] == b'Attached':
				repl = b'1' # attached to device (no process has been created)
			elif args[0] == b'fThreadInfo':
				cores = self._cpu_dbg.get_active_cores()
				repl = b'm' + b','.join([str(i+1).encode('ascii') for i in cores])
				logging.info('Returning thread list: %s', repl)
			elif args[0] == b'sThreadInfo':
				repl = b'l' # end of list
			elif args[0] == b'ThreadExtraInfo':
				thread_id = int(args[1])
				repl = binascii.hexlify('core {0}'.format(thread_id - 1).encode('ascii'))
			else:
				logging.warning('Unknown GDB packet: %s', data)
		elif cmd == b'Q': # set
			args = re.split(b'[,:]', arg)
			if args[0] == b'StartNoAckMode':
				logging.debug('Starting no-ack mode')
				self._gdb_conn.start_no_ack_mode()
				repl = b'OK'
			else:
				logging.warning('Unknown GDB packet: %s', data)
		elif cmd == b'H': # set thread
			op = arg[0]
			thread_id = int(arg[1:])
			if thread_id in [-1, 0]:
				# all cores - ignore
				repl = b'OK'
			else:
				core_id = thread_id - 1
				if self._cpu_dbg.is_core_active(core_id):
					self._cpu_dbg.set_core(core_id)
					logging.info('GDB changed core to %d (op %s)', core_id, op)
					repl = b'OK'
				else:
					logging.warning('Invalid thread ID in %s', data)
					repl = b'E01'
		elif cmd == b'T': # check if thread is alive
			core_id = int(arg) - 1
			active = self._cpu_dbg.is_core_active(core_id)
			repl = b'OK' if active else b'E01'
		else:
			logging.warning('Unknown GDB packet: %s', data)

		# Send reply
		logging.debug('Handled GDB packet %s - reply %s', data, repl)
		self._gdb_conn.send_packet(repl)
		return not exit

	def wait_for_exception(self):
		logging.info('Waiting for exception...')
		interruptible = True
		self._sig = SIGTRAP
		while True:
			logging.debug('Waiting for context...')
			try:
				if self._cpu_dbg.wait_for_context(interruptible=interruptible):
					break
			except DebuggerInterruptedException:
				logging.info('Interrupted...')

			interruptible = False
			self._sig = SIGINT
			self._cpu_dbg.break_cpu()

		logging.info('CPU stopped')
		self.select_best_core()

	def run(self):
		self._setup_done = False
		self._cpu_dbg.break_cpu()
		while True:
			try:
				data = self._gdb_conn.get_packet()
				if not data:
					logging.debug('Got no packet')
					return
				if not self.handle_gdb_packet(data):
					logging.info('Detaching')
					return
			except DebuggerDisconnectedException:
				logging.info('Debugger disconnected')
				return
			except TargetDisconnectedException:
				logging.info('Target disconnected')
				return


class GdbLoggingHandler(logging.Handler):
	def __init__(self, gdb_conn):
		logging.Handler.__init__(self)
		self._gdb_conn = gdb_conn

	def emit(self, record):
		log_entry = self.format(record)
		self._gdb_conn.send_packet(b'O ' + log_entry.encode('utf-8'))


class PipePair():
	def __init__(self, read_pipe_name, write_pipe_name):
		# Note: server connects read pipe first so use reversed order here
		self._write_pipe = open(write_pipe_name, 'wb', buffering=0)
		while True:
			try:
				if os.name == 'nt':
					# On Windows client cannot open pipe until server calls ConnectNamedPipe.
					# Simulator uses two pipes and it calls ConnectNamedPipe synchronously so we have to wait util second pipe is available.
					# In C app WaitNamedPipe should be used. Standard Python does not have API for that so wait 100ms instead.
					time.sleep(0.1)
				self._read_pipe = open(read_pipe_name, 'rb', buffering=0)
			except:
				continue
			else:
				break

	def write(self, *args, **kwargs):
		res = self._write_pipe.write(*args, **kwargs)
		return res

	def read(self, *args, **kwargs):
		res = self._read_pipe.read(*args, **kwargs)
		return res

	def close(self):
		self._read_pipe.close()
		self._write_pipe.close()


class Options:
	def __init__(self):
		self.gdb_port = GDB_PORT
		self.unix_socket = None
		self.dbg_port = DBG_PORT
		self.dbg_baudrate = DBG_BAUDRATE
		self.log_level = logging.INFO
		self.log_filename = None
		self.debug_proto_log_path = None
		self.mcu_name = 'ml605'
		self.pipe = False
	
	def _show_help(self):
		print('Usage: dbgserver.py [OPTIONS]\n')
		print('Options:')
		print('  -p, --port=DBG_PORT            path to debug port device')
		print('                                 (default: {0})'.format(DBG_PORT))
		print('  -b, --baudrate=BAUDRATE        debug port baudrate (default: {0})'.format(DBG_BAUDRATE))
		print('  -g, --gdbport=TCP_PORT         listen on TCP port for GDB connection')
		print('                                 (default: {0})'.format(GDB_PORT))
		print('  -u, --unix-socket=FILE         use Unix domain socket for GDB connection')
		print('  --pipe                         use standard streams for GDB connection')
		print('  -l, --log=LEVEL                logging level - one of: DEBUG, INFO (default),')
		print('                                 WARNING, ERROR, CRITICAL')
		print('  -o, --log-file=FILE            log to FILE')
		print('  --debug-proto-log=FILE         log debug proto to FILE (slow)')
		print('  --mcu=ml605|ccnv1              enable compatibility with mcu')

	def parse(self, argv):
		opts, args = getopt.getopt(argv,
			'hp:b:g:u:l:o:',
			['help', 'port=', 'baudrate=', 'gdbport=', 'unix-socket=', 'log=', 'log-file=', 'debug-proto-log=',
				'mcu=', 'pipe'])
		for opt, arg in opts:
			if opt in ('-h', '--help'):
				self._show_help()
				sys.exit(0)
			elif opt in ('-p', '--port'):
				self.dbg_port = arg
			elif opt in ('-b', '--baudrate'):
				self.dbg_baudrate = int(arg)
			elif opt in ('-g', '--gdbport'):
				self.gdb_port = int(arg)
			elif opt in ('-u', '--unix-socket'):
				self.unix_socket = arg
			elif opt in ('--pipe'):
				self.pipe = True
			elif opt in ('-l', '--log'):
				self.log_level = getattr(logging, arg.upper())
				if not isinstance(self.log_level, int):
					raise ValueError('Invalid log level: %s' % arg)
			elif opt in ('-o', '--log-file'):
				self.log_filename = arg
			elif opt in ('--debug-proto-log'):
				self.debug_proto_log_path = arg
			elif opt in ('--mcu'):
				if arg not in ('ml605', 'ccnv1'):
					raise ValueError('Invalid mcu name: %s' % arg)
				self.mcu_name = arg


def create_socket_for_gdb(opts):
	# Setup socket for GDB connection
	if opts.pipe:
		return None
	elif not opts.unix_socket:
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		sock.bind(('', opts.gdb_port))
		logging.info('Listening on TCP port %d...', opts.gdb_port)
	else:
		if os.path.exists(opts.unix_socket):
			st = os.stat(opts.unix_socket)
			if st and stat.S_ISSOCK(st.st_mode):
				os.unlink(opts.unix_socket)

		sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
		sock.bind(opts.unix_socket)
		logging.info('Listening on unix socket %s...', opts.unix_socket)

	if not opts.pipe:
		sock.listen(5)

	return sock


def create_dbg_stream(opts):
	# Check if dbg_port is valid
	if opts.debug_proto_log_path:
		logging.warning('Logging debug protocol may slow down the debug server!')
	if opts.dbg_port.startswith('pipe:'):
		dbg_pipe_name = opts.dbg_port.split(':')[1]
		logging.debug('Connecting to debug pipe...')
		pipe_name_prefix = '\\\\.\\pipe\\' if os.name == 'nt' else ''
		read_pipe_name = pipe_name_prefix + dbg_pipe_name + '.out'
		write_pipe_name = pipe_name_prefix + dbg_pipe_name + '.in'
		dbg_stream = PipePair(read_pipe_name, write_pipe_name)
		logging.info('Connected to debug pipe %s', dbg_pipe_name)
	else:
		# HACK: On Linux if dsrdtr is disabled pyserial always does TIOCMBIS ioctl to set DTR which fails for socat
		# created devices. Enabled dsrdtr seems to not harm communication with real hardware.
		# On Windows enabled dsrdtr breaks debugging real hardware so it needs to be disabled there.
		dsrdtr = (os.name != 'nt')

		# Note: pyserial doesnt detect port closing when reading data from another thread without timeout
		dbg_stream = serial.Serial(port=opts.dbg_port, baudrate=opts.dbg_baudrate, rtscts=False, dsrdtr=dsrdtr)
		logging.info('Connected to debug port %s (baudrate %d)', opts.dbg_port, opts.dbg_baudrate)
	
	dbg_stream = StreamLoggingWrapper(dbg_stream, opts.debug_proto_log_path)
	return dbg_stream


def main(argv):
	# Parse command line arguments
	opts = Options()
	opts.parse(argv)
	
	if opts.pipe:
		# Ignore SIGINT in pipe mode
		signal.signal(signal.SIGINT, signal.SIG_IGN)

	# Setup logging
	#logging.basicConfig(level=log_level, format='%(levelname)s: %(message)s', filename=log_filename, filemode='w')
	logging.srcfile = None
	logging.logThreads = 0
	logging.logProcesses = 0

	logging.getLogger().setLevel(opts.log_level)
	formatter = logging.Formatter('%(levelname)s: %(message)s')

	ch = logging.StreamHandler() # uses stderr
	ch.setFormatter(formatter)
	if opts.pipe:
		ch.setLevel(logging.ERROR)
	logging.getLogger().addHandler(ch)

	if opts.log_filename:
		fh = logging.FileHandler(opts.log_filename)
		fh.setFormatter(formatter)
		logging.getLogger().addHandler(fh)

	# Install exception handler
	# Note: it does not work in threads: https://bugs.python.org/issue1230540
	def exception_handler(exc_type, exc_value, exc_traceback):
		if issubclass(exc_type, KeyboardInterrupt):
			sys.__excepthook__(exc_type, exc_value, exc_traceback)
			return
		logging.critical('Uncaught exception', exc_info=(exc_type, exc_value, exc_traceback))
	sys.excepthook = exception_handler

	sock = create_socket_for_gdb(opts)
	dbg_stream = create_dbg_stream(opts)
	cpu_dbg = CpuDebug(dbg_stream, opts.mcu_name)

	try:
		while True:
			if not opts.pipe:
				logging.info('Waiting for GDB client...')
				client, addr = sock.accept() # GDB client connected
				logging.info('GDB client connected: %s', addr)
			else:
				client = None

			gdb_conn = GdbConn(client, cpu_dbg.get_input_thread())
			bridge = DbgBridge(gdb_conn, cpu_dbg)

			if opts.pipe and False:
				gdb_handler = GdbLoggingHandler(gdb_conn)
				logging.getLogger().addHandler(gdb_handler)

			try:
				bridge.run()
			except serial.SerialException as e:
				logging.exception('Serial exception')
			except socket.error as e:
				logging.exception('Socket error')

			if client:
				client.close()

			logging.info('GDB client disconnected.')
			if opts.pipe:
				break
	except KeyboardInterrupt:
		logging.info('Exiting...')

	logging.debug('Closing debug stream...')
	cpu_dbg.get_input_thread().closing = True
	if os.name == 'nt' and opts.dbg_port.startswith('pipe:'):
		# HACK: On Windows closing pipe does not interrupt read request on a pipe.
		# To workaround it send a basic command to MCU to make it respond with something and wake up
		# the input thread.
		dbg_stream.write(b'I')
	try:
		dbg_stream.close()
	except Exception as e:
		logging.warn('Exception when closing debug stream: %s', e)
	logging.debug('Closed debug stream.')

	if opts.unix_socket:
		os.unlink(opts.unix_socket)

	if opts.pipe:
		# Wait a moment so GDB has chance to read last packets. Not sleeping causes GDB error on Windows.
		time.sleep(0.1)
	logging.debug('Exiting from main thread')


if __name__ == '__main__':
	main(sys.argv[1:])
