#include "main.h"

/*!
 * Статически выделенная память под
 * нужны задач, мигающих светодиодами.
 */
USER_OS_STATIC_STACK_TYPE				tbLedThread[1][ TB_LED_TASK_SIZE ];
USER_OS_STATIC_TASK_STRUCT_TYPE			tsLedThread[1];

extern GlobalPort		mcGpObj;
extern Pin				led1Obj;
extern wdt				wdtObj;

extern "C" {

/*!
 * Задача для мигания светодиодом.
 */
void ledThread ( void* p ) {
	Pin* pObj = ( Pin* )p;
	while (1) {
		pObj->toggle();
		vTaskDelay(500);
	}
}

const rcc_cfg mcu_clock[] = {
	/*!
	 * Индекс: 0
	 * Источник: внешний резонатор на 25 МГц. !! Установить в  cfg/stm32f4xx_hal_conf.h
	 * PCLK:			168 МГц.
	 * AHB1:			168 МГц.
	 * APB2:			84 МГц.
	 * APB1:			42 МГц.
	 */
    {
    	.OscillatorType = RCC_OSCILLATORTYPE_HSE,
		.HSEState       = RCC_HSE_ON,
		.LSEState       = RCC_LSE_OFF,
		.HSIState       = RCC_HSI_OFF,
		.HSICalibrationValue    = RCC_HSICALIBRATION_DEFAULT,
		.LSIState               = RCC_LSI_OFF,
		.PLL                    = {
			.PLLState               = RCC_PLL_ON,
			.PLLSource              = RCC_PLLSOURCE_HSE,
			.PLLM                   = 25,
			.PLLN                   = 336,
			.PLLP                   = RCC_PLLP_DIV2,
			.PLLQ                   = 4
    	},

		.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK,
		.AHBCLKDivider  = RCC_SYSCLK_DIV1,
		.APB1CLKDivider = RCC_HCLK_DIV4,
		.APB2CLKDivider = RCC_HCLK_DIV2,

		.f_latency = FLASH_LATENCY_3
	}
};

int main ( void ) {

	//Включение шин тактирования задействованных для gpio
	mcGpObj.reinitAllPorts();

	//настройка тактирования
	Rcc clock(mcu_clock, 1);
	clock.setCfg(0);

/*
	uint32_t sys = HAL_RCC_GetSysClockFreq();
	uint32_t hcl = HAL_RCC_GetHCLKFreq();
	uint32_t apb1 = HAL_RCC_GetPCLK1Freq();
	uint32_t apb2 = HAL_RCC_GetPCLK2Freq();
*/

	//включение вачдога
	wdtObj.init();
	//устанавливаем run_time timeout
	wdtObj.reset();

	//включение предсказателя


	USER_OS_STATIC_TASK_CREATE( ledThread, "ledTask1", TB_LED_TASK_SIZE, &led1Obj, 3, &tbLedThread[0][0], &tsLedThread[0] );
	vTaskStartScheduler();
    while ( true );
}

}
