#include "port.h"

const pin_cfg led1Cfg = { GPIOB, { GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };

const pin_cfg mcGpCfg[] = {
	led1Cfg
};

Pin	led1Obj( &led1Cfg );

GlobalPort		mcGpObj( mcGpCfg, 1 );
