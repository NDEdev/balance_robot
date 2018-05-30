#include "port.h"

const pinCfg led1Cfg = { GPIOB, { GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };
const pinCfg pinTim2Cfg = { GPIOD, { GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };
const pinCfg pinTim9Cfg = { GPIOD, { GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };

/*
 * MPU SPI + SOL_READY_INTERRAPT_PIN
 */
const pinCfg spiMosiCfg = { GPIOA, { GPIO_PIN_7, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI1 } };
const pinCfg spiMisoCfg = { GPIOA, { GPIO_PIN_6, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI1 } };
const pinCfg spiClkCfg  = { GPIOB, { GPIO_PIN_3, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI1 } };
const pinCfg spiCsCfg   = { GPIOB, { GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };
const pinCfg mpuIntCfg  = { GPIOC, { GPIO_PIN_4, GPIO_MODE_IT_RISING, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };


/*
 * Motor driver pins config
 */

//  motor (1) left config
const pinCfg mlEnCfg = {GPIOD, { GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };
const pinCfg mlDirCfg = {GPIOD, { GPIO_PIN_11, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };
const pinCfg mlPwmCfg = {GPIOD, { GPIO_PIN_13, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF2_TIM4 } };
const pinCfg mlAdcCfg = {GPIOA, { GPIO_PIN_1, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };


// motor (2) right config
const pinCfg mrEnCfg = {GPIOD, { GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };
const pinCfg mrDirCfg = {GPIOD, { GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };
const pinCfg mrPwmCfg = {GPIOB, { GPIO_PIN_14, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF9_TIM12 } };
const pinCfg mrAdcCfg = {GPIOA, { GPIO_PIN_2, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };


const pinCfg mcGpCfg[] = {
	led1Cfg, pinTim2Cfg, pinTim9Cfg,

	// (MPU) Spi Pins + sol ready
	spiMosiCfg, spiMisoCfg, spiClkCfg, spiCsCfg, mpuIntCfg,

	// left motor driver  cfg
	mlEnCfg, mlDirCfg, mlPwmCfg, mlAdcCfg,

	// right motor driver cfg
	mrEnCfg, mrDirCfg, mrPwmCfg, mrAdcCfg,

};

Pin	led1Obj( &led1Cfg );
Pin tim2Obj( &pinTim2Cfg );
Pin tim9Obj( &pinTim9Cfg );

/*
 * Mpu pins obj
 */

Pin spiMpuMosi( &spiMosiCfg );
Pin spiMpuMiso( &spiMisoCfg );
Pin spiMpuClk( &spiClkCfg );
Pin spiMpuCs( &spiCsCfg );
Pin	mpuInt	(&mpuIntCfg);

/*
 * Motor driver pins obj
 */
Pin mlEn	( &mlEnCfg );
Pin mlDir	( &mlDirCfg );

Pin mrEn 	( &mrEnCfg );
Pin mrDir	( &mrDirCfg );

// Обьект включения всех  шин тактирования
GlobalPort		mcGpObj( mcGpCfg, sizeof(mcGpCfg)/sizeof(mcGpCfg[0]) );
