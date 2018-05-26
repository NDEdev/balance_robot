/*
 * current_sensor.cpp
 *
 *  Created on: May 16, 2018
 *      Author: demid
 */

#include "current_sensor.h"
#include "user_os.h"

CurrentSensor::CurrentSensor(AdcOneChannelBase *_adc, double _transferCoeff, double _voltageBias, double _gain)
		: adc(_adc), transferCoeff(_transferCoeff), voltageBias(_voltageBias), gain(_gain)
{
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
	float voltVal = ((float)adcVal/4096.0) * 3.3;

	// Вычитаем смещение
	float voltBiased = voltVal - this->voltageBias;

	//  Получаем реально значения наряжения без усиления
	float voltReal = voltBiased / this->gain;

	// Получим ток в млА
	float	currentVal = (voltReal * this->transferCoeff)*1000.0; // Ток в млА

	val = currentVal;
	rv = true;
	return rv;
}
