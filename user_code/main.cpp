#include "main.h"
#include "clock_config_check.h"
#include "hardware_init.h"
#include "balancer_driver.h"
#include "imu_filter.h"
#include "imu_filter_interface.h"


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
#include "mc_hardware_interfaces_adc.h"
#include "adc.h"
#include "current_sensor.h"
#include "current_sensor_interface.h"
#include "mc_hardware_interfaces_timer.h"
#include "timer.h"
#include "uart.h"
#include "mc_hardware_interfaces_uart.h"

extern AdcOneChannel adcLeft;
extern AdcOneChannel adcRight;
extern Mpu6500 mpuObj;
extern CurrentSensor currentSensorLeft;
extern CurrentSensor currentSensorRight;

extern TimPwmOneChannel motorLeftPwm;
extern TimPwmOneChannel motorRightPwm;

extern Uart uartObj;

void ledThread ( void* p ) {
	Pin* pObj = ( Pin* )p;
	Imu::imu_sol_t sol;

	AdcOneChannelBase *adc1 = &adcLeft;
	AdcOneChannelBase *adc2 = &adcRight;

	CurrentSensorInterface *curSensLeft = &currentSensorLeft;
	CurrentSensorInterface *curSensRight = &currentSensorRight;

	TimPwmOneChannelBase *pwmLeft = &motorLeftPwm;
	TimPwmOneChannelBase *pwmRight = &motorRightPwm;

	UartBase *uartTelem = &uartObj;

	uint32_t adc_mesure1 = 0;
	uint32_t adc_mesure2 = 0;

	float currentMesureLeft = 0;
	float currentMesureRight = 0;

	pwmLeft->on();
	pwmRight->on();

	pwmLeft->setDuty(0.5);
	pwmRight->setDuty(0.5);

	uartTelem->on();
	const char testUartBuff[] = "HELLO";

	while (1) {
		pObj->toggle();

		/// Debug
		adc_mesure1 = adc1->getMeasurement();
		adc_mesure2 = adc2->getMeasurement();

		curSensLeft->getCurrent(currentMesureLeft);
		curSensRight->getCurrent(currentMesureRight);

		uartTelem->tx((uint8_t *)testUartBuff, sizeof(testUartBuff), 50000);

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

const ImuFilter::imu_filter_cfg_t imu_cfg = {
		.accel_ang_axis = 2,
		.angrate_axis = 1,
		.filter_coeff = 0.01
};

int main ( void ) {

	// Включение шин <a> задействованных для gpio
	mcGpObj.reinitAllPorts();

	// Настройка тактирования
	Rcc clock(mcu_clock, 1);
	clock.setCfg(0);

	// Проверка настройки тактирования с помошью таймеров
//	clock_config_check_init();

	// Включение вачдога
//	wdtObj.reinit();
	// Устанавливаем run_time timeout
//	wdtObj.reset();

	// Включение предсказателя
	prefetch_enable();

	// Инициализация переферии
	hardware_init();

	// Инициализация интерфейса к переферии и объектов связаных с ней
//	ImuFilter imu(&mpuObj, imu_cfg);
	//imu.init();

	// Инициализация дравера балансиров
	//BalancerDriver balancer;
	//balancer.set_imu(&imu);

	//TODO : СМОТРИ ТРЕЛЛО

	// создания задачи для мигания светодиодом
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
