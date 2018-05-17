/*
 * motor_driver.h
 *
 *  Created on: May 16, 2018
 *      Author: demid
 */

#ifndef USER_CODE_MOTOR_DRIVER_H_
#define USER_CODE_MOTOR_DRIVER_H_

#ifdef __cplusplus

#include "user_os.h"
#include "motor_driver_interface.h"
#include "mc_hardware_interfaces_adc.h"
#include "mc_hardware_interfaces_pin.h"
#include "mc_hardware_interfaces_timer.h"
#include "current_sensor_interface.h"

class MotorDriver : public MotorDriverInterface {

#define TASK_STACK_SIZES 300

	// Process

	float	desiredTorque;
	const float maxCurren; //  Максимальный ток в млА который может проекать через мотор в текущей конфигурации. Заблокированный мотор.

	// Сервисные данные
	bool 									inited;
	USER_OS_STATIC_BIN_SEMAPHORE			mutex;
	USER_OS_STATIC_STACK_TYPE 				p_stack[TASK_STACK_SIZES];
	USER_OS_STATIC_TASK_STRUCT_TYPE			p_struct;
	USER_OS_STATIC_BIN_SEMAPHORE_BUFFER		mutexBuff;

	// Поток упрвления вращением (реулятор наряжения на двигателе)
	static void		motorControlThread		(void *p);

	// Интерфейсы к переферии
	PinBase						*enPin;				// Enable/Disable driver
	PinBase						*dirPin;			// Set direction rotation CW/CCW
	TimPwmOneChannelBase		*pwm;				// Set voltage on motor
	CurrentSensorInterface		*mcs;				// Motor current sensor


	float 			getDesiredTorque		(void);

	// Реализация интерфейса
	bool 			isReadyToWork			(void);
	void 			enable					(bool state);
	bool 			setTorque				(float torq);
	bool 			setSpeed				(float speed);
	bool 			setPosition				(float pos);

public:
	// Constructor
	MotorDriver(CurrentSensorInterface *_motorCurrentSens, TimPwmOneChannelBase *_pwm, PinBase *_enPin, PinBase *_dirPin, float _maxCurrent);
	// Destructor
	virtual ~MotorDriver();

	bool 			init					(void);

};

#endif

#endif /* USER_CODE_MOTOR_DRIVER_H_ */
