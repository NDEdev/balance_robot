/*
 * motor_driver.cpp
 *
 *  Created on: May 16, 2018
 *      Author: demid
 */

#include "motor_driver.h"


MotorDriver::MotorDriver(CurrentSensorInterface *_motorCurrentSens, TimPwmOneChannelBase *_pwm, PinBase *_enPin, PinBase *_dirPin, float _maxCurrent): maxCurren(_maxCurrent) {
	configASSERT(_motorCurrentSens);
	configASSERT(_pwm);
	configASSERT(_enPin);
	configASSERT(_dirPin);
	configASSERT(_maxCurrent);

	desiredTorque = 0;
	inited  = false;
	mcs 	= _motorCurrentSens;
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


void MotorDriver::motorControlThread(void *p){
	MotorDriver *o = (MotorDriver*) p;
	float currentCurren = 0;
	float currentTorque = 0;
	float desireTorque = 0;

	// инициализация
	o->pwm->setDuty(0);
	if(o->pwm->on() != BASE_RESULT::OK )
		configASSERT(0);

	o->enPin->set(true);

	// инициализация завершена
	o->inited = true;

	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 10;
	xLastWakeTime = xTaskGetTickCount();
	while(true){
		vTaskDelayUntil( &xLastWakeTime, xFrequency );

		// получим значение тока
		if(!o->mcs->getCurrent(currentCurren)){
			// Ошибка чтения
			continue;
		}

		// текущее значение момента
		currentTorque = currentCurren/o->maxCurren;

		// желаемое значение момента
		desireTorque = o->getDesiredTorque();

		// regulator


		// для отладки шлём на прямую шим в зависимости от момента


		// перед установкой направления сброси шимм напряжения в 0 во избежания рывка
		o->pwm->setDuty(0);

		// установим направление вращения согласно знаку момнта
		if(desireTorque >= 0){
			o->dirPin->set(true);
		} else {
			o->dirPin->set(false);
		}

		// установка целевого значения шимм сигнала напряжения на двигатель
		o->pwm->setDuty(desireTorque);
	}
}


float MotorDriver::getDesiredTorque	(void){
	float rv = 0;

	if(USER_OS_TAKE_MUTEX(mutex, portMAX_DELAY) == pdTRUE){
		rv = this->desiredTorque;
		USER_OS_GIVE_MUTEX(mutex);
	}

	return rv;
}


/// Реализация интерфейса

bool MotorDriver::isReadyToWork(void){
	return inited;
}

void MotorDriver::enable(bool state){
	enPin->set(state);
}

bool MotorDriver::setTorque(float torq){
	if(USER_OS_TAKE_MUTEX(mutex, portMAX_DELAY) == pdTRUE){
		this->desiredTorque = torq;
		USER_OS_GIVE_MUTEX(mutex);
	}

	return true;
}

bool MotorDriver::setSpeed(float speed){
	// обраотка метода не реализована
	return false;
}

bool MotorDriver::setPosition(float pos){
	// обраотка метода не реализована
	return false;
}
