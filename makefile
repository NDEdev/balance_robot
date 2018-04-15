-include freertos/freertos.mk
-include mcu_hardlib/mcu_hardlib.mk

TARGET = stm32f4_template

GCC_DIR = /opt/gcc-arm-none-eabi/bin/
SYSTEM = $(GCC_DIR)arm-none-eabi


PROJ_DEFS = __VFP_FP__ STM32F4xx STM32F407xx HSE_VALUE=25000000 USE_HAL_DRIVER DEBUG  
PROJ_DEFS +=  _USE_MATH_DEFINES
CPU := cortex-m4
LD_FILES = mcu_hardlib/CMSIS/Device/STM32F407VETx_FLASH.ld
LD_DIRS = obj/bin
LIBS = mcu_hardlib.a freertos.a

CFLAGS  = -mcpu=$(CPU) -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
LDFLAGS = -mcpu=$(CPU) -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -g3 -fmessage-length=0 -ffunction-sections -fdata-sections -Wall -Wextra -g3 -nostartfiles -Xlinker --gc-sections --specs=nano.specs -Wl,-u,vfprintf -lm -u _printf_float -u _scanf_float
ARFLAGS = cr

MAIN_PROJ_OPTIMIZATION = -g3 -O0
OVERRIDE_EFLIB_OPTIMIZATION = -g3 -O0
OVERRIDE_MCU_HARDLIB_OPTIMIZATION =
OVERRIDE_FREERTOS_OPTIMIZATION =



#Неизменяемая часть

# Перечисляем компоненты toolchain-а.
CC      = $(SYSTEM)-gcc
CPP     = $(SYSTEM)-g++
CCDEP   = $(SYSTEM)-gcc
LD      = $(SYSTEM)-g++
AR      = $(SYSTEM)-ar
AS      = $(SYSTEM)-gcc
OBJCOPY = $(SYSTEM)-objcopy
OBJDUMP	= $(SYSTEM)-objdump
GDB		= $(SYSTEM)-gdb
SIZE	= $(SYSTEM)-size

PROJ_CFG_DIR = cfg
BUILD_PATHS += $(PROJ_PATHS) $(FREERTOS_DIRS) $(MCU_HARDLIB_DIRS) $(PROJ_CFG_DIR)

CFLAGS += $(addprefix -I, $(BUILD_PATHS))
CFLAGS += $(addprefix -D, $(PROJ_DEFS))
LDFLAGS +=  $(addprefix -T , $(LD_FILES))#добавим файлы ld к строке -nostartfiles -Xlinker --gc-sections
LDFLAGS += $(addprefix -L, $(LD_DIRS)) 
LDFLAGS += -Wl,-Map="obj/bin/$(TARGET).map"

LIB_FLAGS = $(addprefix -l, $(LIBS:%.a=%)) -lm
LIB_FLAGS += -lc -lnosys
LIBS_FULL = $(addprefix obj/bin/lib, $(LIBS))
TARGET_FULL := bin/$(TARGET).elf
TARGET_FULL_BIN := bin/$(TARGET).bin

MAIN_PROJ_L_CFLAGS =$(CFLAGS) -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections\
	-Wall -Wextra -std=gnu99 -fshort-enums

MAIN_PROJ_L_CPPFLAGS = $(CFLAGS) -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections \
	-Wall -Wextra -std=c++14 -fshort-enums

FREERTOS_OUT = freertos.a
FREERTOS_OUT_FULL = obj/bin/lib$(FREERTOS_OUT)
MCU_HARDLIB_OUT = mcu_hardlib.a
MCU_HARDLIB_OUT_FULL = obj/bin/lib$(MCU_HARDLIB_OUT)

.PHONY: all clean

PROJ_PATHS = $(shell find user_code -maxdepth 5 -type d)
DIR_FLAGS = $(addprefix -I, $(PROJ_PATHS))

SRCS_MASKS:= *.c *.cpp $(addsuffix /*.c, $(PROJ_PATHS)) $(addsuffix /*.cpp, $(PROJ_PATHS))
SRCS_UF = $(wildcard $(SRCS_MASKS))
SRCS_UF := $(subst //,/,$(SRCS_UF))
ifdef PROJ_EXCLUDED_SRCS
	EXCL_FIRST := $(word 1,$(PROJ_EXCLUDED_SRCS))
	EXCL_STRING := -name $(EXCL_FIRST)  $(addprefix -o -name ,$(filter-out $(EXCL_FIRST),$(PROJ_EXCLUDED_SRCS)))
	EXCL_SOURCES := $(shell find ./ -type f $(EXCL_STRING))
	EXCL_SOURCES := $(subst ./,,$(EXCL_SOURCES))
	SRCS := $(filter-out $(EXCL_SOURCES),$(SRCS_UF))
else
	SRCS = $(SRCS_UF)
endif

OBJS = $(addprefix obj/o/$(TARGET)/, $(patsubst %.c,%.o, $(patsubst %.cpp,%.o,$(SRCS))))
DEPS = $(OBJS:.o=.d)

pre_build:
	@echo 'Building target: $(TARGET)'
	@echo 'Creating object folders'
	@echo '  '
	@mkdir -p bin
	@mkdir -p obj
	@mkdir -p obj/bin
	@mkdir -p obj/o
	@mkdir -p obj/o/$(TARGET)
	
all: pre_build $(TARGET).siz

dbg:
	@echo $(CFLAGS)

$(TARGET).siz: dbg $(TARGET_FULL) $(TARGET_FULL_BIN)
	@echo 'Invoking: Cross ARM GNU Print Size'
	@arm-none-eabi-size --format=berkeley "$(TARGET_FULL)"
	@echo ' '

$(TARGET_FULL): $(OBJS) $(LIBS_FULL) $(LD_FILES)
	@echo 'Invoking: Cross ARM C++ Linker'
	@$(LD) $(LDFLAGS) -o $(TARGET_FULL) -Wl,--start-group -Wl,--whole-archive $(LIB_FLAGS) \
		-Wl,--no-whole-archive $(OBJS) -Wl,--end-group -Wl,--no-wchar-size-warning
	@echo 'Finished building target: $@'
	@echo ' '
	
$(TARGET_FULL_BIN): $(TARGET_FULL) #Для прошивки с помощью st-utill
	@echo 'Invoking: Cross ARM objcopy'
	@$(OBJCOPY) -O binary $(TARGET_FULL) $(TARGET_FULL_BIN)
	@echo 'Finished building target: $@'
	@echo ' '

obj/o/$(TARGET)/%.o: %.c  makefile 
	@mkdir -p $(dir $@)
	@echo [CC] $<
	@$(CC) $(MAIN_PROJ_L_CFLAGS) $(MAIN_PROJ_OPTIMIZATION) $(DIR_FLAGS) -MMD -MP -c $< -o $@ -MT $@
	
all:freertos mcu_hardlib

freertos: $(FREERTOS_OUT)
$(FREERTOS_OUT): $(FREERTOS_OUT_FULL)

mcu_hardlib: $(MCU_HARDLIB_OUT)
$(MCU_HARDLIB_OUT): $(MCU_HARDLIB_OUT_FULL)

clean: clean_freertos mcu_hardlib_clean clean_proj

clean_proj: 
	rm -r -f obj/o/$(TARGET)
	rm bin/$(TARGET).bin bin/$(TARGET).elf


