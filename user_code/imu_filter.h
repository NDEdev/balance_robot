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

	typedef struct{
		int 	accel_ang_axis;
		int 	angrate_axis;
		float 	filter_coeff; // коэффициент комплиментарного фильтра
	}imu_filter_cfg_t;

	#define TASK_STACK_SIZES 300

	Imu::ImuSensorInterface 		*imu_sensor;
	const int 						accel_ang_axis; 	// ось imu котторая соответсвует вертикальной оси балансира
	const int 						angrate_axis;	 	// ось imu которая соответсвует горизонтальной оси балансира
	const float						filter_coeff;
	bool 							inited;
	USER_OS_STATIC_BIN_SEMAPHORE	mutex;



	//solution
	ImuFilterInreface::imu_sol_t 	sol;

	USER_OS_STATIC_STACK_TYPE 				p_stack[TASK_STACK_SIZES];
	USER_OS_STATIC_TASK_STRUCT_TYPE			p_struct;
	USER_OS_STATIC_BIN_SEMAPHORE_BUFFER		mutexBuff;

	static void 		imuThread			(void *p);

public:
	ImuFilter( imu_filter_cfg_t cfg);
	virtual ~ImuFilter();

	/// Реализция интерфейса
	void setImuSensor(Imu::ImuSensorInterface *imuSensObj);
	bool init(void);
	float normalize(float val);
};

#endif /* USER_CODE_IMU_FILTER_H_ */
