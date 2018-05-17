/*
 * mc_pwm.cpp
 *
 *  Created on: May 17, 2018
 *      Author: demid
 */

#include "timer.h"

/*
 * TODO : УТОЧНИТЬ НАСТРОЙКИ ТАКТИРОВАНИЯ ТАЙМЕРА СОГЛАСНО CUBEMX
 */

const clkTimBaseCfg clockTimMotorLeftCfg = {
		.period = 		10000,
		.prescaler =	155,
		.pulse	= 		0
};

const timPwmOneChannelCfg pwmMotorLeftCfg = {
		.tim =			TIM1,
		.cfg =			&clockTimMotorLeftCfg,
		.countCfg =		1000,
		.outChannel =  	TIM_CHANNEL_1,
		.polarity =		TIM_OCPOLARITY_HIGH
};

const clkTimBaseCfg clockTimMotorRightCfg = {
		.period = 		10000,
		.prescaler =	155,
		.pulse = 		0
};

const timPwmOneChannelCfg pwmMotorRightCfg = {
		.tim =			TIM2,
		.cfg =			&clockTimMotorRightCfg,
		.countCfg =		1000,
		.outChannel =  	TIM_CHANNEL_1,
		.polarity =		TIM_OCPOLARITY_HIGH
};

TimPwmOneChannel motorLeftPwm	(&pwmMotorLeftCfg);
TimPwmOneChannel motorRightPwm	(&pwmMotorRightCfg);

