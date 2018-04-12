-include freertos/freertos.mk

GCC_DIR = /usr/bin/
SYSTEM = $(GCC_DIR)arm-none-eabi

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

PROJ_DEFS = __VFP_FP__ STM32F4xx STM32F415xx HSE_VALUE=16000000 USE_HAL_DRIVER DEBUG 
PROJ_DEFS += 
CPU := cortex-m4
LD_FILES = mcu_hardlib/stm/stm32f4/mem.ld mcu_hardlib/stm/sections.ld
LD_DIRS = obj/bin
LIBS = mcu_hardlib.a eflib.a freertos.a

CFLAGS  = -mcpu=$(CPU) -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
LDFLAGS = -mcpu=$(CPU) -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -g3 -fmessage-length=0 -ffunction-sections -fdata-sections -Wall -Wextra -g3 -nostartfiles -Xlinker --gc-sections --specs=nano.specs -Wl,-u,vfprintf -lm -u _printf_float -u _scanf_float
ARFLAGS = cr

FREERTOS_OUT = freertos.a
FREERTOS_OUT_FULL = obj/bin/lib$(FREERTOS_OUT)

.PHONY: all clean

all:freertos
freertos: $(FREERTOS_OUT)
$(FREERTOS_OUT): $(FREERTOS_OUT_FULL)

clean: clean_freertos


