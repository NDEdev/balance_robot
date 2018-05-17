/*
 * mc_timers.cpp
 *
 *  Created on: May 3, 2018
 *      Author: demid
 */


#include "timer.h"
#include "capture_frequency.h"

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

//*******************************************************
//	Измерение частоты
//*******************************************************

// TODO : НАСТРРОИТЬ КОНФИГ СОГЛАСНО CUBE MX
timCaptureCfg tim1CaptureCfg = {
	.tim						=	TIM1,
	.prescaler					=	100 - 1,
	.minTickValue				=	105,
	.countUpForResetChannel		=	13,
	.maxCountUpTimerPeriod		=	26
};

TimCapture tim1CaptureObj( &tim1CaptureCfg, 1 );

// TODO : НАСТРРОИТЬ КОНФИГ СОГЛАСНО CUBE MX
timCaptureCfg tim2CaptureCfg = {
	.tim						=	TIM2,
	.prescaler					=	100 - 1,
	.minTickValue				=	105,
	.countUpForResetChannel		=	13,
	.maxCountUpTimerPeriod		=	26
};

TimCapture tim2CaptureObj( &tim2CaptureCfg, 1 );

captureFrequencyChannelCfg	captureFrequencyChannelArrayCfg[] = {
	{
		.timer			=	&tim1CaptureObj,
		.channel		=	1
	},
	{
		.timer			=	&tim2CaptureObj,
		.channel		=	2
	}
};

CaptureFrequencyCfg	captureFrequencyCfg = {
	.channelCfg				=	captureFrequencyChannelArrayCfg,
	.channelCount			=	2,
	.taskPrio				=	4
};

CaptureFrequency	captureFrequencyObj( &captureFrequencyCfg );


//*******************************************************
//	Измерение положения
//*******************************************************

const timEncoderCfg tim3EncCfg= {
		.tim 		= TIM3,
		.period 	= 1920,
		.countCfg	= 0
};

TimEncoder tim3EncObj(&tim3EncCfg);

const timEncoderCfg tim4EncCfg= {
		.tim 		= TIM4,
		.period 	= 1920,
		.countCfg	= 0
};

TimEncoder tim4EncObj(&tim4EncCfg);

