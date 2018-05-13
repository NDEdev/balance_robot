/*
 * imu_filter.h
 *
 *  Created on: May 12, 2018
 *      Author: demid
 */

#ifndef USER_CODE_IMU_FILTER_H_
#define USER_CODE_IMU_FILTER_H_

#include "user_os.h"
#include "imu_filter_interface.h"
#include "imu_sensor_interface.h"

class ImuFilter: public ImuFilterInreface {


	#define TASK_STACK_SIZES 300

	Imu::ImuSensorInterface 		*imu_sensor;
	const int 						accel_ang_axis; 	// номер оси imu которая соответсвует вертикальной оси балансира. X:0, Y:1, Z:2
	const int 						angrate_axis;	 	// номер оси imu которая соответсвует горизонтальной оси балансира.  X:3, Y:4, Z:5
	const float						filter_coeff;
	bool 							inited;
	USER_OS_STATIC_BIN_SEMAPHORE	mutex;
	USER_OS_STATIC_BIN_SEMAPHORE	extSync;

	// Solution
	ImuFilterInreface::imu_sol_t 	sol;

	USER_OS_STATIC_STACK_TYPE 				p_stack[TASK_STACK_SIZES];
	USER_OS_STATIC_TASK_STRUCT_TYPE			p_struct;
	USER_OS_STATIC_BIN_SEMAPHORE_BUFFER		mutexBuff;
	USER_OS_STATIC_BIN_SEMAPHORE_BUFFER		extSyncBuff;

	static void 		imuThread			(void *p);

public:

	typedef struct{
		int 	accel_ang_axis;
		int 	angrate_axis;
		float 	filter_coeff; // коэффициент комплиментарного фильтра
	}imu_filter_cfg_t;

	ImuFilter	( Imu::ImuSensorInterface  *_imu_sensor ,imu_filter_cfg_t cfg);
	virtual ~ImuFilter();

	bool 	init					(void);
	float 	normalize				(float val);

	/// Реализция интерфейса
	bool 	isReadyToWork			(void);
	bool 	getSol					(imu_sol_t &sol);
	bool 	getSolBlocked			(imu_sol_t &sol);

};

#endif /* USER_CODE_IMU_FILTER_H_ */
