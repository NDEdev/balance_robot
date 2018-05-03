#include "adc.h"

AdcOneChannel::AdcOneChannel( const AdcOneChannelCfg* const cfg ) {
	this->adcSt.Instance					= cfg->ADCx;
	this->adcSt.Init.ClockPrescaler		= cfg->clockPrescaler;
	this->adcSt.Init.Resolution			= cfg->resolution;
	this->adcSt.Init.DataAlign				= cfg->dataAlign;
	this->adcSt.Init.ScanConvMode			= ENABLE;
	this->adcSt.Init.EOCSelection			= ADC_EOC_SINGLE_CONV;
	this->adcSt.Init.ContinuousConvMode	= ENABLE;
	this->adcSt.Init.NbrOfConversion		= 1;
	this->adcSt.Init.ExternalTrigConv		= ADC_SOFTWARE_START;

	this->channelCfg.Channel				= cfg->channel;
	this->channelCfg.Rank					= 1;
	this->channelCfg.SamplingTime			= cfg->samplingTime;
}

bool AdcOneChannel::reinit ( void ) const {
	this->clkEnable();
	HAL_ADC_DeInit( &this->adcSt );

	HAL_StatusTypeDef r;
	r = HAL_ADC_Init( &this->adcSt );
	if ( r != HAL_OK ) return false;
	r = HAL_ADC_ConfigChannel( &this->adcSt, &this->channelCfg );
	if ( r != HAL_OK ) return false;

	return true;
}

void AdcOneChannel::clkEnable ( void ) const {
	switch( ( uint32_t )this->adcSt.Instance ) {
		case ADC1_BASE: __HAL_RCC_ADC1_CLK_ENABLE(); break;
		case ADC2_BASE: __HAL_RCC_ADC2_CLK_ENABLE(); break;
		case ADC3_BASE: __HAL_RCC_ADC3_CLK_ENABLE(); break;
	}
}

void AdcOneChannel::clkDisable ( void ) const {
	switch( ( uint32_t )this->adcSt.Instance ) {
		case ADC1_BASE:	__HAL_RCC_ADC1_CLK_DISABLE(); break;
		case ADC2_BASE:	__HAL_RCC_ADC2_CLK_DISABLE(); break;
		case ADC3_BASE:	__HAL_RCC_ADC3_CLK_DISABLE(); break;
	}
}

bool AdcOneChannel::startContinuousConversion ( void ) const {
	HAL_StatusTypeDef r;
	r = HAL_ADC_Start( &this->adcSt );
	if ( r != HAL_OK ) return false;
	return true;
}

bool AdcOneChannel::stopContinuousConversion ( void ) const {
	HAL_StatusTypeDef r;
	r = HAL_ADC_Stop( &this->adcSt );
	if ( r != HAL_OK ) return false;
	return true;
}

void AdcOneChannel::getMeasurement ( uint32_t& channel_measurement ) const {
	channel_measurement = HAL_ADC_GetValue( &this->adcSt );
}
