
export

MCU_HARDLIB_DEFS = 
MCU_HARDLIB_CFLAGS = $(CFLAGS) -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -std=gnu99
ifdef OVERRIDE_MCU_HARDLIB_OPTIMIZATION
	MCU_HARDLIB_CFLAGS += $(OVERRIDE_MCU_HARDLIB_OPTIMIZATION)
else
	MCU_HARDLIB_CFLAGS += -Os -g3
endif

MCU_HARDLIB_OUT = mcu_hardlib.a
MCU_HARDLIB_OUT_FULL = obj/bin/lib$(MCU_HARDLIB_OUT)
#флаги, индивидуальные для разных платформ
#ifneq срабатывает если такая строка есть (здесь используется как "если не равно пустому месту")
MCU_HARDLIB_DIRS = $(shell find mcu_hardlib/CMSIS -maxdepth 5 -type d)
MCU_HARDLIB_DIRS += $(shell find mcu_hardlib/Src -maxdepth 5 -type d)
MCU_HARDLIB_DIRS += $(shell find mcu_hardlib/Inc -maxdepth 5 -type d)
MCU_HARDLIB_DIRS += $(shell find mcu_hardlib/newlib -maxdepth 5 -type d)

MCU_HARDLIB_DIRS += mcu_hardlib/ 


MCU_HARDLIB_AS_MAP := $(addsuffix /*.s, $(MCU_HARDLIB_DIRS))
MCU_HARDLIB_MAP := $(addsuffix /*.c, $(MCU_HARDLIB_DIRS))
MCU_HARDLIB_AS_SRCS := $(wildcard $(MCU_HARDLIB_AS_MAP))
MCU_HARDLIB_SRCS := $(wildcard $(MCU_HARDLIB_MAP))
MCU_HARDLIB_DEPS = $(addprefix obj/o/,$(MCU_HARDLIB_SRCS:.c=.d))

#добавим к папкам глобальные пути, чтобы нашелся eflibConfig.h
MCU_HARDLIB_DIRS += $(PROJ_PATHS)
MCU_HARDLIB_DIR_FLAGS = $(addprefix -I, $(MCU_HARDLIB_DIRS))
MCU_HARDLIB_DFLAGS = $(addprefix -D, $(MCU_HARDLIB_DEFS)) $(addprefix -D, $(PROJ_DEFS))

MCU_HARDLIB_AS_OBJS = $(addprefix obj/o/, $(patsubst %.s,%.o,$(MCU_HARDLIB_AS_SRCS)))
MCU_HARDLIB_OBJS = $(addprefix obj/o/, $(patsubst %.c,%.o,$(MCU_HARDLIB_SRCS))) 



$(MCU_HARDLIB_OUT_FULL): $(MCU_HARDLIB_OBJS) $(MCU_HARDLIB_AS_OBJS)
#nobj/o/mcu_hardlib/stm/stm32f4/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.o
#mcu_hardlib_diag
	@mkdir -p obj/bin
	@echo [AR] $@ 
	@$(AR) $(ARFLAGS) $@  $(MCU_HARDLIB_OBJS) $(MCU_HARDLIB_AS_OBJS)
	@echo finished building mcu_hardlib
	@echo ' '


obj/o/mcu_hardlib/%.o: mcu_hardlib/%.c mcu_hardlib/mcu_hardlib.mk makefile
	@mkdir -p $(dir $@)
	@echo [CC] $<
	@$(CC) $(MCU_HARDLIB_CFLAGS) $(MCU_HARDLIB_DFLAGS) $(MCU_HARDLIB_DIR_FLAGS) -MMD -MP -c $< -o  $@ -MT $@

$(MCU_HARDLIB_AS_OBJS): $(MCU_HARDLIB_AS_SRCS) mcu_hardlib/mcu_hardlib.mk makefile		#для .s файлов (например startup_stm32f103xb.s)
	@mkdir -p $(dir $@)
	@echo [AS] $<
	@arm-none-eabi-as -mcpu=$(CPU) -mthumb -g $< -o $@
	
.PHONY: mcu_hardlib_clean
mcu_hardlib_clean:
	-rm -rf obj/o/mcu_hardlib
	-rm obj/bin/lib$(MCU_HARDLIB_OUT)

-include $(MCU_HARDLIB_DEPS)