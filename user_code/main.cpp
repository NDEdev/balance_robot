#include "main.h"
#include "clock_config_check.h"

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

static void prefetch_enable(void);


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

	//проверка настройки тактирования с помошью таймеров
	clock_config_check_init();

	//включение вачдога
	wdtObj.init();
	//устанавливаем run_time timeout
	wdtObj.reset();

	//включение предсказателя
	prefetch_enable();

	//создания задачи для мигания светодиодом
	USER_OS_STATIC_TASK_CREATE( ledThread, "ledTask1", TB_LED_TASK_SIZE, &led1Obj, 3, &tbLedThread[0][0], &tsLedThread[0] );
	vTaskStartScheduler();
    while ( true );
}

static void prefetch_enable(void){
	__HAL_FLASH_INSTRUCTION_CACHE_ENABLE();
	__HAL_FLASH_DATA_CACHE_ENABLE();
	__HAL_FLASH_PREFETCH_BUFFER_ENABLE();
}

}
