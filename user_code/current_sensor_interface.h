/*
 * current_sensor_interface.h
 *
 *  Created on: May 16, 2018
 *      Author: demid
 */

#ifndef USER_CODE_CURRENT_SENSOR_INTERFACE_H_
#define USER_CODE_CURRENT_SENSOR_INTERFACE_H_

#ifdef __cplusplus

class CurrentSensorInterface{
public:
	virtual bool isReadyToWork(void) = 0;
	virtual bool getCurrent (float &val) = 0;
};

#endif

#endif /* USER_CODE_CURRENT_SENSOR_INTERFACE_H_ */
