/*
 * mc_pwm.cpp
 *
 *  Created on: May 17, 2018
 *      Author: demid
 */

#include "timer.h"

/*
 * pwm period 15 us
 */

const uint32_t pwm_period_us = 15;

const uint32_t timer_bus_clock_mhz = 168;
const uint32_t _period = (timer_bus_clock_mhz*pwm_period_us)/(((timer_bus_clock_mhz*pwm_period_us)/0xFFFF)+1);
const uint32_t _prescaler = (timer_bus_clock_mhz*pwm_period_us)/0xFFFF;

const clkTimBaseCfg clockTimMotorLeftCfg = {
		.period = 		16800,
		.prescaler =	10000,
		.pulse	= 		0
};

const timPwmOneChannelCfg pwmMotorLeftCfg = {
		.tim =			TIM4,
		.cfg =			&clockTimMotorLeftCfg,
		.countCfg =		1,
		.outChannel =  	TIM_CHANNEL_2,
		.polarity =		TIM_OCPOLARITY_LOW
};

const clkTimBaseCfg clockTimMotorRightCfg = {
		.period = 		16800,
		.prescaler =	10000,
		.pulse = 		0
};

const timPwmOneChannelCfg pwmMotorRightCfg = {
		.tim =			TIM4,
		.cfg =			&clockTimMotorRightCfg,
		.countCfg =		1,
		.outChannel =  	TIM_CHANNEL_1,
		.polarity =		TIM_OCPOLARITY_LOW
};

TimPwmOneChannel motorLeftPwm	(&pwmMotorLeftCfg);
TimPwmOneChannel motorRightPwm	(&pwmMotorRightCfg);

