/*
 * motor_driver_interface.h
 *
 *  Created on: May 16, 2018
 *      Author: demid
 */

#ifndef USER_CODE_MOTOR_DRIVER_INTERFACE_H_
#define USER_CODE_MOTOR_DRIVER_INTERFACE_H_

#ifdef __cplusplus

class MotorDriverInterface {
public:

	/*!
	 * Метод возвращает true если модуль инициализирован
	 */
	virtual bool isReadyToWork(void) = 0;

	/*!
	 * Метод переводит драйвер двигателя в состояние включен если параметр state = true, выключен если state = false
	 */
	virtual void enable(bool state) = 0;

	/*!
	 * Метод выставляет требуемое значение момента (параметр torq) от 0 до 1 которое дожен стабилизировать двигатель
	 */
	virtual bool setTorque(float torq) = 0;

	/*!
	 * Метод выставляет требуемое значение скорости (параметр speed) от 0 до 1 которое дожен стабилизировать двигатель
	 */
	virtual bool setSpeed(float speed) = 0;

	/*!
	 * Метод выставляет требуемое значение положения (параметр pos) от 0 до 1 которое дожен стабилизировать двигатель
	 */
	virtual bool setPosition(float pos) = 0;
};

#endif

#endif /* USER_CODE_MOTOR_DRIVER_INTERFACE_H_ */
