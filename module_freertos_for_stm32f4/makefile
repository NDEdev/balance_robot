# Собираем все необходимые .h файлы FreeRTOS.

ifndef MODULE_FREE_RTOS_OPTIMIZATION
	MODULE_FREE_RTOS_OPTIMIZATION = -g3 -O0
endif

# FreeRTOS.h должен обязательно идти первым! 
FREE_RTOS_H_FILE			:= module_freertos_for_stm32f4/FreeRTOS.h
FREE_RTOS_H_FILE			+= $(wildcard module_freertos_for_stm32f4/include/*.h)

# Директории, в которых лежат файлы FreeRTOS.
FREE_RTOS_DIR				:= module_freertos_for_stm32f4
FREE_RTOS_DIR				+= module_freertos_for_stm32f4/include

# Подставляем перед каждым путем директории префикс -I.
FREE_RTOS_PATH				:= $(addprefix -I, $(FREE_RTOS_DIR))

# Получаем список .c файлов ( путь + файл.c ).
FREE_RTOS_C_FILE			:= $(wildcard module_freertos_for_stm32f4/*.c)

# Получаем список .o файлов ( путь + файл.o ).
# Сначала прибавляем префикс ( чтобы все .o лежали в отдельной директории
# с сохранением иерархии.
FREE_RTOS_OBJ_FILE			:= $(addprefix build/obj/, $(FREE_RTOS_C_FILE))
# Затем меняем у всех .c на .o.
FREE_RTOS_OBJ_FILE			:= $(patsubst %.c, %.o, $(FREE_RTOS_OBJ_FILE))
	
FREE_RTOS_INCLUDE_FILE		:= -include"./module_freertos_for_stm32f4/include/stack_macros.h"

# Сборка FreeRTOS.
# $< - текущий .c файл (зависемость).
# $@ - текущая цель (создаваемый .o файл).
# $(dir путь) - создает папки для того, чтобы путь файла существовал.
build/obj/module_freertos_for_stm32f4/%.o:	module_freertos_for_stm32f4/%.c 
	@echo [CC] $<
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) $(MODULE_FREE_RTOS_OPTIMIZATION) $(FREE_RTOS_PATH) $(USER_CFG_PATH) $(FREE_RTOS_INCLUDE_FILE) -c $< -o $@


# Добавляем к общим переменным проекта.
PROJECT_PATH				+= $(FREE_RTOS_PATH)
PROJECT_OBJ_FILE			+= $(FREE_RTOS_OBJ_FILE)