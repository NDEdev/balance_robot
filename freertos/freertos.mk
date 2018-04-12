export

FREERTOS_CFLAGS = $(CFLAGS)  -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra

ifdef OVERRIDE_FREERTOS_OPTIMIZATION
	FREERTOS_CFLAGS += $(OVERRIDE_FREERTOS_OPTIMIZATION)
else
	FREERTOS_CFLAGS += -Os -g3
endif

FREERTOS_OUT = freertos.a
FREERTOS_OUT_FULL = obj/bin/lib$(FREERTOS_OUT)
FREERTOS_DIRS = freertos freertos/portable freertos/source/include freertos/include freertos/source freertos/portable/cortex-m4
#добавим к папкам глобальные пути, чтобы нашелся FreeRTOSConfig.h

#FREERTOS_SRCS := $(shell find D:/fsoft/kdvs/freertos -maxdepth 20 -name '*.c')
FREERTOS_SRCS_MAP := $(addsuffix /*.c, $(FREERTOS_DIRS))
FREERTOS_SRCS := $(wildcard $(FREERTOS_SRCS_MAP))
FREERTOS_DEPS := $(addprefix obj/o/,$(FREERTOS_SRCS:.c=.d))

FREERTOS_DIR_FLAGS = $(addprefix -I, $(FREERTOS_DIRS))
FREERTOS_OBJS = $(addprefix obj/o/, $(patsubst %.c,%.o,$(FREERTOS_SRCS))) 


$(FREERTOS_OUT_FULL): $(FREERTOS_OBJS)
	@mkdir -p obj/bin
	@echo [AR] $@
	@$(AR) $(ARFLAGS) $@ $(FREERTOS_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	
	
obj/o/freertos/%.o: freertos/%.c freertos/freertos.mk makefile
	@mkdir -p $(dir $@)
	@echo [CC] $<
	@$(CC) $(FREERTOS_CFLAGS) $(FREERTOS_DIR_FLAGS) -MMD -MP -c $< -o  $@ -MT $@

.PHONY: clean_freertos
clean_freertos:
	-rm -rf obj/o/freertos
	-rm obj/bin/libfreertos.a

-include $(FREERTOS_DEPS)