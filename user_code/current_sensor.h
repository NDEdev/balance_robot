/*
 * current_sensor.h
 *
 *  Created on: May 16, 2018
 *      Author: demid
 */

#ifndef USER_CODE_CURRENT_SENSOR_H_
#define USER_CODE_CURRENT_SENSOR_H_

#ifdef __cplusplus

#include "current_sensor_interface.h"
#include "mc_hardware_interfaces_adc.h"

class CurrentSensor : public CurrentSensorInterface {

	bool 				inited;
	const double 		transferCoeff; // Коэффициент преобразования напряжения в ток. Размероность Амп/Вол
	AdcOneChannelBase	*adc;

	bool 				isReadyToWork	(void);
	bool 				getCurrent 		(float &val);

public:
	// _transferCoeff - Коэффициент преобразования напряжения в ток. Размероность Амп/Вол
	CurrentSensor(AdcOneChannelBase *_adc, double _transferCoeff);
	virtual ~CurrentSensor();
};

#endif

#endif /* USER_CODE_CURRENT_SENSOR_H_ */
