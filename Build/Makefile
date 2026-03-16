# ******************************************************************************************
#   Filename    : Makefile
#
#   Author      : Chalandi Amine
#
#   Owner       : Chalandi Amine
#
#   Date        : 22.11.2022
#
#   Description : Build system
#
# ******************************************************************************************

############################################################################################
# Defines
############################################################################################
PRJ_NAME    = Baremetal_Milk-V_multicore_nosdk
OUTPUT_DIR  = $(CURDIR)/../Output
OBJ_DIR     = $(OUTPUT_DIR)/obj
LD_SCRIPT   = $(SRC_DIR)/Memory_Map.ld
SRC_DIR     = $(CURDIR)/../Code

PYTHON      = python
ERR_MSG_FORMATER_SCRIPT = $(CURDIR)/../Tools/scripts/CompilerErrorFormater.py
LINKER_ERR_MSG_FORMATER_SCRIPT = $(CURDIR)/../Tools/scripts/LinkerErrorFormater.py
FORMAT_LINKER_ERR =


FIPTOOL_PATH = ../Tools/fiptool

ifeq ($(OS), Windows_NT)
    FIPTOOL = wsl $(FIPTOOL_PATH)/fiptool
else
    FIPTOOL = $(FIPTOOL_PATH)/fiptool
endif

FSBL         = $(FIPTOOL_PATH)/cv180x.bin
DDR_PARAM    = $(FIPTOOL_PATH)/ddr_param.bin
DUMMY_FW     = $(FIPTOOL_PATH)/empty.bin

SCRIPT_PATCH_BOOT_HEADER_SIZE = ../Tools/scripts/PatchImageBootHeader.py

RTOS           = 

LOCKDIR := $(OBJ_DIR)/err_formatter.lock

############################################################################################
# Toolchain
############################################################################################
TOOLCHAIN = $(subst \,/,$(shell echo $$TOOLCHAIN_GCC_T_HEAD))

AS      = $(TOOLCHAIN)-gcc
CC      = $(TOOLCHAIN)-gcc
CPP     = $(TOOLCHAIN)-g++
LD      = $(TOOLCHAIN)-gcc
OBJDUMP = $(TOOLCHAIN)-objdump
OBJCOPY = $(TOOLCHAIN)-objcopy
SIZE    = $(TOOLCHAIN)-size
READELF = $(TOOLCHAIN)-readelf

ARCH = -march=rv64imafdcvxthead  \
       -mabi=lp64f               \
       -mcmodel=medany           \
       -msmall-data-limit=0      \
       -falign-functions=8       \
       -fomit-frame-pointer


DEFS = -DPRINTF_INCLUDE_CONFIG_H

############################################################################################
# Optimization Compiler flags
############################################################################################

OPT_MODIFIED_O2 = -O2                               \
                  -fno-reorder-blocks-and-partition \
                  -fno-reorder-functions

NO_OPT = -O0

OPT = $(OPT_MODIFIED_O2)

############################################################################################
# GCC Compiler verbose flags
############################################################################################

VERBOSE_GCC = -frecord-gcc-switches -fverbose-asm

############################################################################################
# C Compiler flags
############################################################################################

COPS  = $(OPT)                                        \
        $(ARCH)                                       \
        $(DEFS)                                       \
        -ffreestanding                                \
        -MD                                           \
        -Wa,-adhln=$(OBJ_DIR)/$(basename $(@F)).lst   \
        -gdwarf-4 -ggdb                               \
        -Wconversion                                  \
        -Wsign-conversion                             \
        -Wunused-parameter                            \
        -Wuninitialized                               \
        -Wmissing-declarations                        \
        -Wshadow                                      \
        -Wunreachable-code                            \
        -Wmissing-include-dirs                        \
        -x c                                          \
        -std=c11                                      \
        -Wall                                         \
        -Wextra                                       \
        -fomit-frame-pointer                          \
        -gdwarf-2                                     \
        -fno-exceptions

############################################################################################
# C++ Compiler flags
############################################################################################

CPPOPS  = $(OPT)                                        \
          $(ARCH)                                       \
          $(DEFS)                                       \
          -ffreestanding                                \
          -Wa,-adhln=$(OBJ_DIR)/$(basename $(@F)).lst   \
          -gdwarf-4 -ggdb                               \
          -Wconversion                                  \
          -Wsign-conversion                             \
          -Wunused-parameter                            \
          -Wuninitialized                               \
          -Wmissing-declarations                        \
          -Wshadow                                      \
          -Wunreachable-code                            \
          -Wmissing-include-dirs                        \
          -Wall                                         \
          -Wextra                                       \
          -fomit-frame-pointer                          \
          -gdwarf-2                                     \
          -fno-exceptions                               \
          -x c++                                        \
          -fno-rtti                                     \
          -fno-use-cxa-atexit                           \
          -fno-nonansi-builtins                         \
          -fno-threadsafe-statics                       \
          -fno-enforce-eh-specs                         \
          -ftemplate-depth=128                          \
          -Wzero-as-null-pointer-constant

############################################################################################
# Assembler flags
############################################################################################
ifeq ($(AS), $(TOOLCHAIN)-as)
  ASOPS =  $(ARCH)       \
           -alh          \
           -g
else
  ASOPS = $(OPT)                                        \
          $(ARCH)                                       \
          $(DEFS)                                       \
          -MD                                           \
          -Wa,-adhln=$(OBJ_DIR)/$(basename $(@F)).lst   \
          -gdwarf-4 -ggdb                               \
          -Wconversion                                  \
          -Wsign-conversion                             \
          -Wunused-parameter                            \
          -Wuninitialized                               \
          -Wmissing-declarations                        \
          -Wshadow                                      \
          -Wunreachable-code                            \
          -Wmissing-include-dirs                        \
          -x assembler                                  \
          -std=c11                                      \
          -Wall                                         \
          -Wextra                                       \
          -fomit-frame-pointer                          \
          -gdwarf-2                                     \
          -fno-exceptions                               
endif

############################################################################################
# Linker flags
############################################################################################

ifeq ($(LD), $(TOOLCHAIN)-ld)
  LOPS = -nostartfiles                          \
         -nostdlib                              \
         $(ARCH)                                \
         $(DEFS)                                \
         -e Startup_Init                        \
         --print-memory-usage                   \
         --print-map                            \
         -dT $(LD_SCRIPT)                       \
         -Map=$(OUTPUT_DIR)/$(PRJ_NAME).map     \
         -z,max-page-size=4096                  
else
  LOPS = -nostartfiles                          \
         -nostdlib                              \
         -fno-lto                               \
         $(ARCH)                                \
         $(DEFS)                                \
         -e _start                              \
         -Wl,--print-memory-usage               \
         -Wl,--print-map                        \
         -Wl,-dT $(LD_SCRIPT)                   \
         -Wl,-Map=$(OUTPUT_DIR)/$(PRJ_NAME).map \
         -Wl,-z,max-page-size=4096              

endif

############################################################################################
# Source Files
############################################################################################

SRC_FILES := $(SRC_DIR)/Appli/main.c            \
             $(SRC_DIR)/Mcal/core.c             \
             $(SRC_DIR)/Startup/boot64.s        \
             $(SRC_DIR)/Startup/intvect.s       \
             $(SRC_DIR)/Startup/mmu.s           \
             $(SRC_DIR)/Startup/Startup.c       \
             $(SRC_DIR)/StdLib/StdLib.c
#             $(SRC_DIR)/StdLib/printf/printf.c  \

############################################################################################
# Include Paths
############################################################################################
INC_FILES := $(SRC_DIR)                        \
             $(SRC_DIR)/Appli                  \
             $(SRC_DIR)/Mcal                   \
             $(SRC_DIR)/Startup                \
             $(SRC_DIR)/StdLib/printf          \
             $(SRC_DIR)/StdLib

############################################################################################
# Rules
############################################################################################

VPATH := $(subst \,/,$(sort $(dir $(SRC_FILES)) $(OBJ_DIR)))
FILES_O := $(addprefix $(OBJ_DIR)/, $(notdir $(addsuffix .o, $(basename $(SRC_FILES)))))

LIB = 

ifeq ($(MAKECMDGOALS), BUILD_STAGE_2)
-include $(subst .o,.d,$(FILES_O))
endif

REBUILD_STAGE_1 : CLEAN PRE_BUILD $(CUSTOM_PRE_BUILD_TARGET)
REBUILD_STAGE_2 : link
REBUILD_STAGE_3 : GENERATE POST_BUILD $(OS_SIZE_INFO_TARGET)

BUILD_STAGE_1   : PRE_BUILD OS_TCB_GEN
BUILD_STAGE_2   : link
BUILD_STAGE_3   : GENERATE POST_BUILD $(CUSTOM_POST_BUILD_TARGET)

############################################################################################
# Recipes
############################################################################################
.PHONY : link
link : $(OUTPUT_DIR)/$(PRJ_NAME).elf
	@-echo "" > /dev/null

.PHONY : PRE_BUILD
PRE_BUILD:
	@-echo +++ Building Milk-V dual-core RISC-V 64-bit baremetal firmware
	@git log -n 1 --decorate-refs=refs/heads/ --pretty=format:"+++ Git branch: %D (%h)" 2>/dev/null || true
	@git log -n 1 --clear-decorations 2> /dev/null > /dev/null || true
	@echo +++ info: "$(shell $(CC) -v 2>&1 | tail -n 1)"
	@echo +++ info: "$(shell make -v 2>&1 | head -n 1)"
	@echo +++ info: "$(shell $(PYTHON) --version 2>&1 | head -n 1)"
	@$(if $(shell test -d $(OBJ_DIR) && echo yes),,mkdir -p $(subst \,/,$(OBJ_DIR)))


.PHONY : POST_BUILD
POST_BUILD:
	@-echo +++ End


.PHONY : CLEAN
CLEAN :
	@-rm -rf $(OUTPUT_DIR)/$(PRJ_NAME).bin     2>/dev/null || true
	@-rm -rf $(OUTPUT_DIR)/$(PRJ_NAME).dis     2>/dev/null || true
	@-rm -rf $(OUTPUT_DIR)/$(PRJ_NAME).elf     2>/dev/null || true
	@-rm -rf $(OUTPUT_DIR)/$(PRJ_NAME).hex     2>/dev/null || true
	@-rm -rf $(OUTPUT_DIR)/$(PRJ_NAME).map     2>/dev/null || true
	@-rm -rf $(OUTPUT_DIR)/$(PRJ_NAME).readelf 2>/dev/null || true
	@-rm -rf $(OUTPUT_DIR)/$(PRJ_NAME).sym     2>/dev/null || true
	@-rm -rf $(OBJ_DIR)                        2>/dev/null || true
	@-mkdir -p $(subst \,/,$(OUTPUT_DIR))


$(OBJ_DIR)/%.o : %.c
	@-echo +++ compile: $(subst \,/,$<) to $(subst \,/,$@)
	@-$(CC) $(COPS) $(addprefix -I, $(INC_FILES)) -c $< -o $(OBJ_DIR)/$(basename $(@F)).o 2> $(OBJ_DIR)/$(basename $(@F)).err
	@-while ! mkdir $(LOCKDIR) 2>/dev/null; do sleep 0.1; done; $(PYTHON) $(ERR_MSG_FORMATER_SCRIPT) $(OBJ_DIR)/$(basename $(@F)).err -COLOR; rmdir $(LOCKDIR)

$(OBJ_DIR)/%.o : %.S
	@-echo +++ compile: $(subst \,/,$<) to $(subst \,/,$@)
	@-$(CC) $(OPT) $(ARCH) $(DEFS) $(addprefix -I, $(INC_FILES)) -c $< -o $(OBJ_DIR)/$(basename $(@F)).o 2> $(OBJ_DIR)/$(basename $(@F)).err
	@-while ! mkdir $(LOCKDIR) 2>/dev/null; do sleep 0.1; done; $(PYTHON) $(ERR_MSG_FORMATER_SCRIPT) $(OBJ_DIR)/$(basename $(@F)).err -COLOR; rmdir $(LOCKDIR)

ifeq ($(AS), $(TOOLCHAIN)-as)
$(OBJ_DIR)/%.o : %.s
	@-echo +++ compile: $(subst \,/,$<) to $(subst \,/,$@)
	@$(AS) $(ASOPS) $< -o $(OBJ_DIR)/$(basename $(@F)).o 2> $(OBJ_DIR)/$(basename $(@F)).err >$(OBJ_DIR)/$(basename $(@F)).lst
	@-while ! mkdir $(LOCKDIR) 2>/dev/null; do sleep 0.1; done; $(PYTHON) $(ERR_MSG_FORMATER_SCRIPT) $(OBJ_DIR)/$(basename $(@F)).err -COLOR; rmdir $(LOCKDIR)
else
$(OBJ_DIR)/%.o : %.s
	@-echo +++ compile: $(subst \,/,$<) to $(subst \,/,$@)
	@-$(CC) $(ASOPS) $(addprefix -I, $(INC_FILES)) -c $< -o $(OBJ_DIR)/$(basename $(@F)).o 2> $(OBJ_DIR)/$(basename $(@F)).err
	@-while ! mkdir $(LOCKDIR) 2>/dev/null; do sleep 0.1; done; $(PYTHON) $(ERR_MSG_FORMATER_SCRIPT) $(OBJ_DIR)/$(basename $(@F)).err -COLOR; rmdir $(LOCKDIR)
endif

$(OBJ_DIR)/%.o : %.cpp
	@-echo +++ compile: $(subst \,/,$<) to $(subst \,/,$@)
	@$(CPP) $(CPPOPS) $(addprefix -I, $(INC_FILES)) -c $< -o $(OBJ_DIR)/$(basename $(@F)).o 2> $(OBJ_DIR)/$(basename $(@F)).err
	@-while ! mkdir $(LOCKDIR) 2>/dev/null; do sleep 0.1; done; $(PYTHON) $(ERR_MSG_FORMATER_SCRIPT) $(OBJ_DIR)/$(basename $(@F)).err -COLOR; rmdir $(LOCKDIR)

$(OUTPUT_DIR)/$(PRJ_NAME).elf : $(FILES_O) $(LD_SCRIPT)
	@-echo +++ link: $(subst \,/,$@)
ifeq ($(FORMAT_LINKER_ERR), )
	@$(LD) $(LOPS) $(FILES_O) $(LIB) -o $(OUTPUT_DIR)/$(PRJ_NAME).elf 2>&1
else
	@$(LD) $(LOPS) $(FILES_O) $(LIB) -o $(OUTPUT_DIR)/$(PRJ_NAME).elf > $(OBJ_DIR)/linker.err 2>&1 || true
	$(PYTHON) $(LINKER_ERR_MSG_FORMATER_SCRIPT) $(OBJ_DIR)/linker.err
endif

.PHONY : GENERATE
GENERATE:
	@$(if $(wildcard $(OUTPUT_DIR)/$(PRJ_NAME).elf), ,$(error Error: Link not succeeded !))
	@-echo +++ generate: $(OUTPUT_DIR)/$(PRJ_NAME).readelf
	@$(READELF) -WhS $(OUTPUT_DIR)/$(PRJ_NAME).elf > $(OUTPUT_DIR)/$(PRJ_NAME).readelf
	@-cat $(OUTPUT_DIR)/$(PRJ_NAME).map >> $(OUTPUT_DIR)/$(PRJ_NAME).readelf
	@-echo +++ generate: $(OUTPUT_DIR)/$(PRJ_NAME).sym
	@$(READELF) -Ws $(OUTPUT_DIR)/$(PRJ_NAME).elf >> $(OUTPUT_DIR)/$(PRJ_NAME).readelf
	@-echo +++ generate: $(OUTPUT_DIR)/$(PRJ_NAME).dis
	@$(OBJDUMP) -d --wide $(OUTPUT_DIR)/$(PRJ_NAME).elf >> $(OUTPUT_DIR)/$(PRJ_NAME).readelf
	@-echo +++ generate: $(OUTPUT_DIR)/$(PRJ_NAME).hex
	@$(OBJCOPY) $(OUTPUT_DIR)/$(PRJ_NAME).elf -O ihex $(OUTPUT_DIR)/$(PRJ_NAME).hex
	@-echo +++ generate: $(OUTPUT_DIR)/$(PRJ_NAME).bin
	@$(OBJCOPY) $(OUTPUT_DIR)/$(PRJ_NAME).elf -O binary $(OUTPUT_DIR)/$(PRJ_NAME).bin
	@-echo +++ generate: $(OUTPUT_DIR)/fip.img
	@-$(FIPTOOL) --fsbl $(FSBL) --ddr_param $(DDR_PARAM) --opensbi ../output/$(PRJ_NAME).bin --uboot $(DUMMY_FW) --rtos $(DUMMY_FW) ../output/fip.bin 2> /dev/null > /dev/null || true




