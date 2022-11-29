ifneq ($(CHIPCRAFT_SDK_LEGACY_ENV_VAR_SUPPORT),1)

ifeq ($(MAKE_RESTARTS),)
 $(info applying rules for setting unified environment variables <CHIPCRAFT_SDK_.*> from legacy ones <CCSDK_.*>)
 $(info update your environment)
endif

 define env_var_unification
 ifneq ($$(CCSDK_$1),)
  CHIPCRAFT_SDK_$1 ?= $$(CCSDK_$1)
  $$(info setting CHIPCRAFT_SDK_$1 to CCSDK_$1 = $$(CCSDK_$1))
 endif
 endef

 $(eval $(call env_var_unification,BOARD))
 $(eval $(call env_var_unification,DBG_BAUDRATE))
 $(eval $(call env_var_unification,DBG_PORT))
 $(eval $(call env_var_unification,HOME))
 $(eval $(call env_var_unification,JTAG_FLAG))
 $(eval $(call env_var_unification,MCU))
 $(eval $(call env_var_unification,TOOLCHAIN_PATH))
 $(eval $(call env_var_unification,UART_BAUDRATE))
 $(eval $(call env_var_unification,UART_PORT))
 $(eval $(call env_var_unification,USE_JTAG))

endif

export CHIPCRAFT_SDK_LEGACY_ENV_VAR_SUPPORT := 1

