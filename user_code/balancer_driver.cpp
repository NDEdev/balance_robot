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

void BalancerDriver::set_imu(ImuFilterInreface *imu_filter){

	configASSERT(imu_filter);

	this->imu = imu_filter;
}
