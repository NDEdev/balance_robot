/*
 * imu_filter_interface.h
 *
 *  Created on: May 12, 2018
 *      Author: demid
 */

#ifndef USER_CODE_IMU_FILTER_INTERFACE_H_
#define USER_CODE_IMU_FILTER_INTERFACE_H_

#ifdef __cplusplus

#include "imu_sensor_interface.h"

class ImuFilterInreface{
public:
	typedef float sol_unit_t;

	typedef struct{
		sol_unit_t	ang[3];			// Rad
		sol_unit_t	ang_rate[3];	// Rad/Sec
	}imu_sol_t;


	/*!
	 *	Метод возвращает true если модуль готов к работу
	 */
	virtual bool isReadyToWork(void) = 0;

	/*
	 *  Неблокирующий метод получения рещения инерциалки.
	 *  Возвращает true если данные sol успешно обновлены.
	 */
	virtual bool getSol(imu_sol_t &sol) = 0;

	/*
	 *  Блокирующий метод получения рещения инерциалки.
	 *  Возвращает true если данные sol успешно обновлены.
	 */
	virtual bool getSolBlocked(imu_sol_t &sol) = 0;

};

#endif

#endif /* USER_CODE_IMU_FILTER_INTERFACE_H_ */
