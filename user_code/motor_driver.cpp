/*
 * motor_driver.cpp
 *
 *  Created on: May 16, 2018
 *      Author: demid
 */

#include "motor_driver.h"


MotorDriver::MotorDriver(AdcOneChannelBase *_adc, TimPwmOneChannelBase *_pwm, PinBase *_enPin, PinBase *_dirPin) {
	configASSERT(_adc);
	configASSERT(_pwm);
	configASSERT(_enPin);
	configASSERT(_dirPin);

	desiredTorque = 0;
	inited  = false;
	adc 	= _adc;
	enPin	= _enPin;
	dirPin 	= _dirPin;
	pwm 	= _pwm;
	mutex = nullptr;

}

MotorDriver::~MotorDriver() {
	// TODO Auto-generated destructor stub
}

bool MotorDriver::init(void){
	mutex = USER_OS_STATIC_MUTEX_CREATE(&mutexBuff);
	USER_OS_STATIC_TASK_CREATE( motorControlThread, "motor", TASK_STACK_SIZES, this, 3, this->p_stack, &this->p_struct );
	return true;
}

bool MotorDriver::getCurretTorque(float &currentTorque){
	bool rv = false;

}

void MotorDriver::motorControlThread(void *p){
	MotorDriver *o = (MotorDriver*) p;
	float currentTorque = 0;
	//инициализация завершена
	o->inited = true;

	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 10;
	xLastWakeTime = xTaskGetTickCount();
	while(true){
		vTaskDelayUntil( &xLastWakeTime, xFrequency );

		//

	}
}
