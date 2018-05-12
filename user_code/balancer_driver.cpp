/*
 * software_init.cpp
 *
 *  Created on: May 12, 2018
 *      Author: demid
 */
#include "user_os.h"
#include "balancer_driver.h"

BalancerDriver::BalancerDriver(void){
	imu = nullptr;
}

BalancerDriver::~BalancerDriver(void){

}

void BalancerDriver::set_imu(ImuFilterInreface *imu_filter, Imu::ImuSensorInterface *imu_sensor){

	configASSERT(imu_filter);
	configASSERT(imu_sensor);

	this->imu = imu_filter;
	this->imu->setImuSensor(imu_sensor);
}
