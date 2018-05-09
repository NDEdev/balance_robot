/*
 * mpu_hw_interface.h
 *
 *  Created on: May 3, 2018
 *      Author: demid
 */

#ifndef USER_CODE_IMU_SENSOR_INTERFACE_H_
#define USER_CODE_IMU_SENSOR_INTERFACE_H_

#ifdef __cplusplus

#include <vector>

namespace Mpu{


typedef struct{
	float gyro[3];
	float accel[3];
	float tempr;
}mpu_sol_t;


class ImuSensorInterface {
public:


/*!
 *  Возвращает true если все инициализировано и готово к работе
 */
	virtual bool isReadyToWork() = 0;

/*!
 * Блокирующий запрос рещения инерциалки.
 * Синхронизируется по вычитыванию данных из микросхемы
 * Возвращается true в случае успеха
 */
	virtual bool getSolBlocked(mpu_sol_t &sol) = 0;

/*
 * Неблокирующий запрос решения
 */
	virtual bool getSol(mpu_sol_t &sol) = 0;

};

}

#endif

#endif /* USER_CODE_IMU_SENSOR_INTERFACE_H_ */
