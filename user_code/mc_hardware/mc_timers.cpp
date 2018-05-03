/*
 * mc_timers.cpp
 *
 *  Created on: May 3, 2018
 *      Author: demid
 */


#include "timer.h"


clkTimBaseCfg		tim9BaseCfg = {
	.period					=	10000,
	.prescaler				=	16800,
	.pulse					=	0
};

TimInterruptCfg		tim1CheckClockConfig = {
	.tim					= TIM9,
	.p_cfg					= &tim9BaseCfg,
	.size_cfg				= 1
};

TimInterrupt		tim9Irq( &tim1CheckClockConfig );

clkTimBaseCfg		tim2BaseCfg = {
	.period					=	10000,
	.prescaler				=	8400,
	.pulse					=	0
};

TimInterruptCfg		tim2CheckClockConfig = {
	.tim					= TIM2,
	.p_cfg					= &tim2BaseCfg,
	.size_cfg				= 1
};

TimInterrupt		tim2Irq( &tim2CheckClockConfig );
