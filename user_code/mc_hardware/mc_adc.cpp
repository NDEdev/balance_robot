/*
 * mc_adc.cpp
 *
 *  Created on: May 17, 2018
 *      Author: demid
 */

#include "adc.h"
#include "stm32f4xx_hal_conf.h"

const AdcOneChannelCfg adcLeftCfg = {
	.ADCx 					= ADC2, // ?????
	.clockPrescaler 		= ADC_CLOCK_SYNC_PCLK_DIV4,
	.resolution 			= ADC_RESOLUTION_12B,
	.dataAlign				= ADC_DATAALIGN_RIGHT,
	.channel				= ADC_CHANNEL_2, // ?????
	.samplingTime			= ADC_SAMPLETIME_15CYCLES
};

const AdcOneChannelCfg adcRightCfg = {
	.ADCx 					= ADC3,  // ?????
	.clockPrescaler 		= ADC_CLOCK_SYNC_PCLK_DIV4,
	.resolution 			= ADC_RESOLUTION_12B,
	.dataAlign				= ADC_DATAALIGN_RIGHT,
	.channel				= ADC_CHANNEL_1, // ?????
	.samplingTime			= ADC_SAMPLETIME_15CYCLES
};

AdcOneChannel adcLeft	(&adcLeftCfg, 0);
AdcOneChannel adcRight	(&adcRightCfg, 0);
