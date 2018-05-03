/*
 * mc_wdt.cpp
 *
 *  Created on: May 3, 2018
 *      Author: demid
 */

#include "wdt.h"
#include "user_os.h"

const wdt_cfg cfg = {
		.task_prio = tskIDLE_PRIORITY + 1,
		.run_time_ms = 300,
		.startup_time_ms = 3000,
		.service_time_ms = 3000
};

wdt wdtObj(&cfg);

