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

static void SystemClock_Config(void);
static void MX_GPIO_Init(void);

#define  TICK_INT_PRIORITY            ((uint32_t)15U)   /*!< tick interrupt priority */


void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

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

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}


HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  /*Configure the SysTick to have interrupt in 1ms time basis*/
  HAL_SYSTICK_Config(SystemCoreClock/1000U);

  /*Configure the SysTick IRQ priority */
  HAL_NVIC_SetPriority(SysTick_IRQn, TickPriority, 0U);

  /* Return function status */
  return HAL_OK;
}


int main(void){
	int a = 0;
	uint32_t sysClock = HAL_RCC_GetSysClockFreq();
	uint32_t sysHcl = HAL_RCC_GetHCLKFreq();
	uint32_t sysPCLK1 = HAL_RCC_GetPCLK1Freq();
	uint32_t sysPCLK2 = HAL_RCC_GetPCLK2Freq();
	HAL_Init();
	MX_GPIO_Init();
	SystemClock_Config();
//	SystemCoreClockUpdate();
	sysClock = HAL_RCC_GetSysClockFreq();
	sysHcl = HAL_RCC_GetHCLKFreq();
	sysPCLK1 = HAL_RCC_GetPCLK1Freq();
	sysPCLK2 = HAL_RCC_GetPCLK2Freq();
//	xTaskCreateStatic(vTask1, "clock_test1", STACK_SIZE, NULL, tskIDLE_PRIORITY, xStack1, &xTaskBuffer1 );
	xTaskCreateStatic(vTask2, "clock_test2", STACK_SIZE, NULL, tskIDLE_PRIORITY, xStack2, &xTaskBuffer2 );
	xPortStartScheduler();
}


static void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  HAL_RCC_OscConfig(&RCC_OscInitStruct) ;

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

    /**Configure the Systick interrupt time
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

static void MX_GPIO_Init(void)
{
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

