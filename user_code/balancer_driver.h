/*
 * software_init.h
 *
 *  Created on: May 12, 2018
 *      Author: demid
 */

#ifndef USER_CODE_BALANCER_DRIVER_H_
#define USER_CODE_BALANCER_DRIVER_H_

#ifdef __cplusplus

#include "imu_filter_interface.h"
#include "imu_sensor_interface.h"

class BalancerDriver{
	ImuFilterInreface *imu;

public:
	BalancerDriver();
	~BalancerDriver();

	void set_imu( ImuFilterInreface *imu_filter);
};

#endif

#endif /* USER_CODE_BALANCER_DRIVER_H_ */
