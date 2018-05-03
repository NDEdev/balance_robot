#include "port.h"

const pin_cfg led1Cfg = { GPIOB, { GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };
const pin_cfg pinTim2Cfg = { GPIOD, { GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };
const pin_cfg pinTim9Cfg = { GPIOD, { GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };

/*
 * MPU SPI
 */
const pin_cfg spiMosiCfg = { GPIOA, { GPIO_PIN_7, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI1 } };
const pin_cfg spiMisoCfg = { GPIOA, { GPIO_PIN_6, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI1 } };
const pin_cfg spiClkCfg  = { GPIOB, { GPIO_PIN_3, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI1 } };
const pin_cfg spiCsCfg   = { GPIOB, { GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };



const pin_cfg mcGpCfg[] = {
	led1Cfg, pinTim2Cfg, pinTim9Cfg,

	//Spi Pins
	spiMosiCfg, spiMisoCfg, spiClkCfg, spiCsCfg

};

Pin	led1Obj( &led1Cfg );
Pin tim2Obj( &pinTim2Cfg );
Pin tim9Obj( &pinTim9Cfg );

/*
 * Spi pins obj
 */

Pin spiMpuMosi( &spiMosiCfg );
Pin spiMpuMiso( &spiMisoCfg );
Pin spiMpuClk( &spiClkCfg );
Pin spiMpuCs( &spiCsCfg );

GlobalPort		mcGpObj( mcGpCfg, sizeof(mcGpCfg)/sizeof(mcGpCfg[0]) );
