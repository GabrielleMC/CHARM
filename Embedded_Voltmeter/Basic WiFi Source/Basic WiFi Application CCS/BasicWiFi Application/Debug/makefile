################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := E:/ti/ccsv5/tools/compiler/msp430_4.1.9

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./list.obj" \
"./coms.obj" \
"./board.obj" \
"./basic_wifi_application.obj" \
-l"libc.a" \
"../lnk_msp430fr5739.cmd" \
"E:/Dropbox/git/CHARM/Embedded_Voltmeter/Basic WiFi Source/Basic WiFi Application CCS/CC3000 Spi/Debug/CC3000 Spi.lib" \
"E:/Dropbox/git/CHARM/Embedded_Voltmeter/Basic WiFi Source/Basic WiFi Application CCS/CC3000HostDriver/Debug/CC3000HostDriver.lib" \
"E:/Dropbox/git/CHARM/Embedded_Voltmeter/Basic WiFi Source/Basic WiFi Application CCS/HyperTerminal Driver/Debug/HyperTerminal Driver.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Library/subdir_vars.mk
-include subdir_rules.mk
-include Library/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: BasicWiFi\ Application.out

# Tool invocations
BasicWiFi\ Application.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"E:/ti/ccsv5/tools/compiler/msp430_4.1.9/bin/cl430" -vmspx --abi=coffabi -O4 --opt_for_speed=0 -g --gcc --define=__CCS__ --define=__MSP430FR5739__ --diag_warning=225 --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal -z --stack_size=368 -m"BasicWiFi Application.map" --heap_size=0 --use_hw_mpy=F5 -i"E:/ti/ccsv5/ccs_base/msp430/include" -i"E:/ti/ccsv5/tools/compiler/msp430_4.1.9/lib" -i"E:/ti/ccsv5/tools/compiler/msp430_4.1.9/include" --reread_libs --warn_sections --xml_link_info="BasicWiFi Application_linkInfo.xml" --rom_model -o "BasicWiFi Application.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(MSP430_EXECUTABLE_OUTPUTS__QUOTED) "BasicWiFi Application.out"
	-$(RM) "basic_wifi_application.pp" "board.pp" "coms.pp" "list.pp" 
	-$(RM) "basic_wifi_application.obj" "board.obj" "coms.obj" "list.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
