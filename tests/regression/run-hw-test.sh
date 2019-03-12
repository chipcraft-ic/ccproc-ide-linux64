#!/bin/bash
stdout_log=${1:-/tmp/cctest.log}
test_end_marker="tests succeeded\\|Passed all tests"
sleep_time=0.5
max_iterations=30

ANSI_RED="\e[91m\e[1m"
ANSI_RESET="\e[0m"

make -s -i term > "$stdout_log" &
term_pid=$!
tail -f "$stdout_log" &
tail_pid=$!
sleep 0.2

make -s ram-write

count=0
while ! grep "$test_end_marker" "$stdout_log" > /dev/null
do
    sleep $sleep_time
    count=$(($count + 1))
    if [ $count -ge $max_iterations ]; then
        echo -ne "${ANSI_RED}Timeout!${ANSI_RESET}\n"
        echo -e "\n_TIMEOUT_\n" > "$stdout_log"
        break
    fi
done

kill $term_pid
kill $tail_pid
# Note: killing make process does not kill ccterm so matching by name is needed
pkill -g 0 ccterm
wait
