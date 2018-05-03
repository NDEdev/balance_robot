#pragma once

#include "mc_hardware_interfaces_timer.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_rcc.h"

/*!
 * Параметры делителя и вершины.
 * Для формирования массива конфигураций
 * таймера в зависимости от выбранной
 * частоты RCC.
 */
struct clkTimBaseCfg {
	const uint16_t					period;					// 0..0xFFFF.
	const uint16_t					prescaler;				// 0..0xFFFF.

	/// Используется только в:
	/// 1. tim_comp_one_channel_cfg
	const uint16_t					pulse;					// 0..0xFFFF.
};

struct TimCounterCfg {
	// Используемый таймер.
	TIM_TypeDef*				tim;

	const clkTimBaseCfg*		const p_cfg;
	uint32_t					size_cfg;
};

class TimCounter : public TimCounterBase {
public:
	TimCounter( const TimCounterCfg* const cfg );
	bool		reinit			( uint32_t cfg_number = 0 );
	bool		on				( void );
	bool		off				( void );
	uint32_t	getCounter		( void );

private:
	const	TimCounterCfg*				const cfg;
	TIM_HandleTypeDef					hal;
};

/*!
 * Таймер предназначен для генерации прямоугольного сигнала.
 */
struct TimCompOneChannelCfg {
	// Используемый таймер.
	TIM_TypeDef*				tim;

	const clkTimBaseCfg*		const p_cfg;
	uint32_t					size_cfg;

	// Параметры выходного канала.
	uint8_t						out_channel;			// TIM_CHANNEL_x.
	uint32_t					polarity;				// TIM_OCPOLARITY_LOW  / TIM_OCPOLARITY_HIGH.

};

class TimCompOneChannel : public TimCompOneChannelBase {
public:
	TimCompOneChannel( const TimCompOneChannelCfg* const cfg );
	bool reinit					( uint32_t cfg_number ) const;
	bool on						( void ) const;
	bool off					( void ) const;

private:
	const	TimCompOneChannelCfg*	const cfg;
	mutable TIM_HandleTypeDef			hal_tim_cfg;
	mutable	TIM_OC_InitTypeDef			hal_tim_ch_cfg;
};

//**********************************************************************
// tim_pwm_one_channel
//**********************************************************************
struct tim_pwm_one_channel_cfg {
	// Используемый таймер.
	TIM_TypeDef*				tim;

	const clkTimBaseCfg*		const p_cfg;
	uint32_t					size_cfg;

	// Параметры выходного канала.
	uint8_t						out_channel;			// TIM_CHANNEL_x.
	uint32_t					polarity;				// TIM_OCPOLARITY_LOW  / TIM_OCPOLARITY_HIGH.
};

class TimPwmOneChannel : public TimPwmOneChannelBase {
public:
	TimPwmOneChannel( const tim_pwm_one_channel_cfg* const cfg );
	bool reinit					( uint32_t cfg_number ) 		const;
	bool on						( void ) 						const;
	bool off					( void ) 						const;
	void duty_set				( float duty )					const;

private:
	const tim_pwm_one_channel_cfg*		const cfg;
	mutable TIM_HandleTypeDef			hal_tim_cfg;
	mutable	TIM_OC_InitTypeDef			hal_tim_ch_cfg;
};

//**********************************************************************
// tim_interrupt
//**********************************************************************
struct TimInterruptCfg {
	TIM_TypeDef*				tim;

	const clkTimBaseCfg*		const p_cfg;
	uint32_t					size_cfg;
};

class TimInterrupt : public TimInterruptBase {
public:
	TimInterrupt( const TimInterruptCfg* const cfg );

	bool reinit						( uint32_t cfg_number = 0 );
	bool on							( void );
	bool off						( void );
	void clearInterruptFlag			( void );

private:
	const TimInterruptCfg*		const cfg;
	TIM_HandleTypeDef			hal_tim_cfg;
};
