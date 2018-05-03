#include "port.h"

const pin_cfg led1Cfg = { GPIOB, { GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };
const pin_cfg pinTim2Cfg = { GPIOD, { GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };
const pin_cfg pinTim9Cfg = { GPIOD, { GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };


const pin_cfg mcGpCfg[] = {
	led1Cfg, pinTim2Cfg, pinTim9Cfg
};

Pin	led1Obj( &led1Cfg );
Pin tim2Obj( &pinTim2Cfg );
Pin tim9Obj( &pinTim9Cfg );

GlobalPort		mcGpObj( mcGpCfg, 3 );
