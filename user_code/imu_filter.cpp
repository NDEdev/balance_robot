/*
 * imu_filter.cpp
 *
 *  Created on: May 12, 2018
 *      Author: demid
 */

#include "imu_filter.h"
#include "math.h"

ImuFilter::ImuFilter(imu_filter_cfg_t cfg) : accel_ang_axis(cfg.accel_ang_axis), angrate_axis(cfg.angrate_axis), filter_coeff(cfg.filter_coeff) {
	inited = false;
	imu_sensor = nullptr;
}

ImuFilter::~ImuFilter() {

}

void ImuFilter::imuThread (void *p){
	ImuFilter *o = (ImuFilter*) p;

	Imu::imu_sol_t raw_sensor_data = {0};
	float inclin_ang_sol = 0;
	float accel_vertical;
	float rad_accel = 0; // угол наклона по акселерометру в радеанах
	float ang_rate_prev = 0;
	double dt_sec = 0;

	// Проверка конфигурации
	if(!o->imu_sensor)
		configASSERT(0); //Сенсор не инициализирован

	// Инициализация началного состояния
	while(!o->imu_sensor->getSolBlocked(raw_sensor_data)){
		vTaskDelay(100); //ошибка чтения
	}

	dt_sec = (double)raw_sensor_data.dt / 1000.0;

	// Номализовать данные акселерометра
	accel_vertical = o->normalize(raw_sensor_data.accel[o->accel_ang_axis]);
	inclin_ang_sol = asin(accel_vertical);

	// Инициализировать начальное состояние по угловой скорости
	ang_rate_prev = raw_sensor_data.gyro[o->angrate_axis];

	while(true){

		if(!o->imu_sensor->getSolBlocked(raw_sensor_data)){
			vTaskDelay(100); // Ошибка чтения
			continue;
		}

		// Пересчитаем время между итерациями к секундам
		dt_sec = (double)raw_sensor_data.dt / 1000.0;

		// Нормализуем значение инклинометра
		accel_vertical = o->normalize(raw_sensor_data.accel[o->accel_ang_axis]);

		//знак угловой скорости и угла по акселерометру должны совпадать
		accel_vertical *= -1;

		// Получение угла по акселерометру
		rad_accel = asin(accel_vertical);

		// Получение угла по аксереометру и гироскопу с помощью инклиментарного фильтра
		inclin_ang_sol = (1.0-o->filter_coeff) * ( inclin_ang_sol +  ang_rate_prev*dt_sec) + o->filter_coeff * rad_accel;

		// Итерируем значение угловой скорости
		ang_rate_prev = raw_sensor_data.gyro[o->angrate_axis];

		// Присвоение решения TODO: !!
		// Выдаче семафора внешней синхронизации
	}
}


bool ImuFilter::init(void){
	mutex = USER_OS_STATIC_MUTEX_CREATE(&mutexBuff);
	USER_OS_STATIC_TASK_CREATE( imuThread, "mpuTask", TASK_STACK_SIZES, this, 3, this->p_stack, &this->p_struct );
	return true;
}

float ImuFilter::normalize(float val){
	float ret = val;
	if(ret > 1){
		ret = 1;
	}
	else if(ret < -1){
		ret = -1;
	}
	return ret;

}

void ImuFilter::setImuSensor(Imu::ImuSensorInterface *imuSensObj){
	configASSERT(imuSensObj);
	this->imu_sensor = imuSensObj;
	inited = true;
}
