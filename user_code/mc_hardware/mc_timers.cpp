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

timInterruptCfg		tim1CheckClockConfig = {
	.tim					= TIM9,
	.cfg					= &tim9BaseCfg,
	.countCfg				= 1
};

TimInterrupt		tim9Irq( &tim1CheckClockConfig );

clkTimBaseCfg		tim2BaseCfg = {
	.period					=	10000,
	.prescaler				=	8400,
	.pulse					=	0
};

timInterruptCfg		tim2CheckClockConfig = {
	.tim					= TIM2,
	.cfg					= &tim2BaseCfg,
	.countCfg				= 1
};

TimInterrupt		tim2Irq( &tim2CheckClockConfig );
