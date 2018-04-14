/*
 * main.c
 *
 *  Created on: Apr 14, 2018
 *      Author: demid
 */

#include "project_config.h"

volatile uint32_t ulVar1 = 0, ulVar2 = 0;

void vTask1( void *pvParameters )
{
    for( ;; )
    {
        ulVar1++;
        taskYIELD();
    }
}

void vTask2( void *pvParameters )
{
    for( ;; )
    {
        ulVar2++;
        vTaskDelay(100);
        taskYIELD();
    }
}



#define STACK_SIZE 200

   StaticTask_t xTaskBuffer1;

   StackType_t xStack1[ STACK_SIZE ];

   StaticTask_t xTaskBuffer2;

   StackType_t xStack2[ STACK_SIZE ];

int main(void){
	int a = 0;
	a++;
	 HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	  /* System interrupt init*/
	  /* MemoryManagement_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	  /* BusFault_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	  /* UsageFault_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
	  /* SVCall_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
	  /* DebugMonitor_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
	  /* PendSV_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
	  /* SysTick_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);

	xTaskCreateStatic(vTask1, "clock_test1", STACK_SIZE, NULL, tskIDLE_PRIORITY, xStack1, &xTaskBuffer1 );
	xTaskCreateStatic(vTask2, "clock_test2", STACK_SIZE, NULL, tskIDLE_PRIORITY, xStack2, &xTaskBuffer2 );
	xPortStartScheduler();
}
