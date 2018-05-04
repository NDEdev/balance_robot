/*
 * mc_wdt.cpp
 *
 *  Created on: May 3, 2018
 *      Author: demid
 */

#include "wdt.h"
#include "stm32f4xx_hal.h"
#include "FreeRTOSConfig.h"

const wdtCfg cfg = {
		.taskPrio = tskIDLE_PRIORITY + 1,
		.runTimeMs = 300,
		.startupTimeMs = 3000,
		.serviceTimeMs = 3000
};

Wdt wdtObj(&cfg, 1);

