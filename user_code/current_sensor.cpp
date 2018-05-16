/*
 * current_sensor.cpp
 *
 *  Created on: May 16, 2018
 *      Author: demid
 */

#include "current_sensor.h"
#include "user_os.h"

CurrentSensor::CurrentSensor(AdcOneChannelBase *_adc, double _transferCoeff) : adc(_adc), transferCoeff(_transferCoeff){
	configASSERT(_adc);
	configASSERT(_transferCoeff);

	this->inited = true;
}

CurrentSensor::~CurrentSensor() {

}


bool CurrentSensor::isReadyToWork(void){
	return inited;
}


bool CurrentSensor::getCurrent(float &val){
	bool rv = false;

	// Получаем значение с АЦП
	uint32_t adcVal = adc->getMeasurement();

	// Преобразуем в вольты
	float 	voltVal = ((float)adcVal/(float)0xFFFF) * 3.3;

	// Получим ток в млА
	float	currentVal = (voltVal * this->transferCoeff)*1000.0; // Ток в млА

	val = currentVal;
	rv = true;
	return rv;
}
