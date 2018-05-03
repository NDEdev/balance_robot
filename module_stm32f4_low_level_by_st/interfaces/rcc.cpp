#include "rcc.h"

RCC_RESULT Rcc::setCfg ( uint32_t number_cfg_set ) const {
    if ( number_cfg_set >= this->number_cfg ) return RCC_RESULT::ERROR_CFG_NUMBER;

    RCC_OscInitTypeDef          osc_cfg;
    RCC_ClkInitTypeDef          clk_cfg;

    osc_cfg.HSEState					= this->array_cfg_st[ number_cfg_set ].HSEState;
    osc_cfg.HSICalibrationValue			= this->array_cfg_st[ number_cfg_set ].HSICalibrationValue;
    osc_cfg.HSIState					= this->array_cfg_st[ number_cfg_set ].HSIState;
    osc_cfg.LSEState					= this->array_cfg_st[ number_cfg_set ].LSEState;
    osc_cfg.LSIState					= this->array_cfg_st[ number_cfg_set ].LSIState;
    osc_cfg.OscillatorType				= this->array_cfg_st[ number_cfg_set ].OscillatorType;
    osc_cfg.PLL.PLLM					= this->array_cfg_st[ number_cfg_set ].PLL.PLLM;
    osc_cfg.PLL.PLLN					= this->array_cfg_st[ number_cfg_set ].PLL.PLLN;
    osc_cfg.PLL.PLLP					= this->array_cfg_st[ number_cfg_set ].PLL.PLLP;
    osc_cfg.PLL.PLLQ					= this->array_cfg_st[ number_cfg_set ].PLL.PLLQ;
    osc_cfg.PLL.PLLSource				= this->array_cfg_st[ number_cfg_set ].PLL.PLLSource;
    osc_cfg.PLL.PLLState				= this->array_cfg_st[ number_cfg_set ].PLL.PLLState;
    clk_cfg.SYSCLKSource				= this->array_cfg_st[ number_cfg_set ].SYSCLKSource;
    clk_cfg.AHBCLKDivider				= this->array_cfg_st[ number_cfg_set ].AHBCLKDivider;
    clk_cfg.APB1CLKDivider				= this->array_cfg_st[ number_cfg_set ].APB1CLKDivider;
    clk_cfg.APB2CLKDivider				= this->array_cfg_st[ number_cfg_set ].APB2CLKDivider;

    HAL_RCC_DeInit();

    if ( HAL_RCC_OscConfig( &osc_cfg ) != HAL_OK )
        return RCC_RESULT::ERROR_OSC_INIT;


    clk_cfg.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	if ( HAL_RCC_ClockConfig( &clk_cfg, this->array_cfg_st[ number_cfg_set ].f_latency ) != HAL_OK )
		return  RCC_RESULT::ERROR_CLK_INIT;

	/*
	clk_cfg.ClockType = RCC_CLOCKTYPE_HCLK;
	if ( HAL_RCC_ClockConfig( &clk_cfg, this->array_cfg_st[ number_cfg_set ].f_latency ) != HAL_OK )
		return  RCC_RESULT::ERROR_CLK_INIT;

	clk_cfg.ClockType = RCC_CLOCKTYPE_PCLK1;
	if ( HAL_RCC_ClockConfig( &clk_cfg, this->array_cfg_st[ number_cfg_set ].f_latency ) != HAL_OK )
		return  RCC_RESULT::ERROR_CLK_INIT;

	clk_cfg.ClockType = RCC_CLOCKTYPE_PCLK2;
	if ( HAL_RCC_ClockConfig( &clk_cfg, this->array_cfg_st[ number_cfg_set ].f_latency ) != HAL_OK )
		return  RCC_RESULT::ERROR_CLK_INIT;*/

    return RCC_RESULT::OK;
}
