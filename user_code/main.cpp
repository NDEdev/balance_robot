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
extern Wdt				wdtObj;



/*!
 * Задача для мигания светодиодом.
 */

/// For debug

#include "imu_sensor_interface.h"
#include "mpu6500.h"

extern Mpu6500 mpuObj;

void ledThread ( void* p ) {
	Pin* pObj = ( Pin* )p;
	Imu::imu_sol_t sol;
	while (1) {
		pObj->toggle();

		/// Debug
		Imu::ImuSensorInterface *imu;
		imu = &mpuObj;

		if(imu->isReadyToWork()){
			imu->getSolBlocked(sol);
		}

	vTaskDelay(500);
	}
}


extern "C" {

static void prefetch_enable(void);




const rccCfg mcu_clock[] = {
	/*!
	 * Индекс: 0
	 * Источник: внешний резонатор на 25 МГц. !! Установить в  cfg/stm32f4xx_hal_conf.h
	 * PCLK:			168 МГц.
	 * AHB1:			168 МГц.
	 * APB2:			84 МГц.
	 * APB1:			42 МГц.
	 */
    {
		.osc = {
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
			}
		},
		.clk = {
			.ClockType 		= RCC_CLOCKTYPE_SYSCLK,
			.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK,
			.AHBCLKDivider  = RCC_SYSCLK_DIV1,
			.APB1CLKDivider = RCC_HCLK_DIV4,
			.APB2CLKDivider = RCC_HCLK_DIV2,
		},

		.fLatency = FLASH_LATENCY_3
	}
};


int main ( void ) {

	//Включение шин <a> задействованных для gpio
	mcGpObj.reinitAllPorts();

	//настройка тактирования
	Rcc clock(mcu_clock, 1);
	clock.setCfg(0);

	//проверка настройки тактирования с помошью таймеров
//	clock_config_check_init();

	//включение вачдога
//	wdtObj.reinit();
	//устанавливаем run_time timeout
//	wdtObj.reset();

	//включение предсказателя
	prefetch_enable();

	//инициализация переферии
	hardware_init();

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
