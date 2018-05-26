/*
 * imu_filter.cpp
 *
 *  Created on: May 12, 2018
 *      Author: demid
 */

#include "imu_filter.h"
#include "math.h"

ImuFilter::ImuFilter(Imu::ImuSensorInterface  *_imu_sensor, imu_filter_cfg_t cfg) : accel_ang_axis(cfg.accel_ang_axis), angrate_axis(cfg.angrate_axis), filter_coeff(cfg.filter_coeff) {
	inited = false;
	imu_sensor = _imu_sensor;
}

ImuFilter::~ImuFilter() {

}

void ImuFilter::imuThread (void *p){
	ImuFilter *o = (ImuFilter*) p;

	Imu::imu_sol_t raw_sensor_data = {0};
	float inclin_ang_sol = 0;
	float accel_vertical;
	float rad_accel = 0; // Угол наклона по акселерометру в радеанах
	float ang_rate_prev = 0;
	double dt_sec = 0;

	// Проверка конфигурации
	if(!o->imu_sensor)
		configASSERT(0); // Сенсор не инициализирован

	while(!o->imu_sensor->isReadyToWork())
		//vTaskDelay(100); // Сенсор не инициализирован TODO: Косяк, Разобраться, всё зависает при попадании сюда

	// Инициализация началного состояния
	while(!o->imu_sensor->getSolBlocked(raw_sensor_data)){
		vTaskDelay(100); // Ошибка получения данных
	}

	dt_sec = (double)raw_sensor_data.dt / 1000.0;

	// Номализовать данные акселерометра
	accel_vertical = o->normalize(raw_sensor_data.accel[o->accel_ang_axis]);
	inclin_ang_sol = asin(accel_vertical);

	// Инициализировать начальное состояние по угловой скорости
	ang_rate_prev = raw_sensor_data.gyro[o->angrate_axis];

	// Инициализация завершена
	o->inited = true;

	while(true){

		if(!o->imu_sensor->getSolBlocked(raw_sensor_data)){
			vTaskDelay(100); // Ошибка получения данных
			continue;
		}

		// Пересчитаем время между итерациями к секундам
		dt_sec = (double)raw_sensor_data.dt / 1000.0;

		// Нормализуем значение инклинометра
		accel_vertical = o->normalize(raw_sensor_data.accel[o->accel_ang_axis]);

		// Знак угловой скорости и угла по акселерометру должны совпадать
		accel_vertical *= -1;

		// Получение угла по акселерометру
		rad_accel = asin(accel_vertical);

		// Получение угла по аксереометру и гироскопу с помощью инклиментарного фильтра
		inclin_ang_sol = (1.0-o->filter_coeff) * ( inclin_ang_sol +  ang_rate_prev*dt_sec) + o->filter_coeff * rad_accel;

		// Итерируем значение угловой скорости
		ang_rate_prev = raw_sensor_data.gyro[o->angrate_axis];

		// Присвоение решения TODO: !!
		if(USER_OS_TAKE_MUTEX(o->mutex, portMAX_DELAY) == pdTRUE){

			// Занулим значения на всех осях кроме используемых для измерения угла наклона балансира и угловой скорости
			for(int i = 0; i < 3; i++){
				o->sol.ang[i] = 0;
				o->sol.ang_rate[i] = 0;

				if(i == o->accel_ang_axis){
					o->sol.ang[i] = inclin_ang_sol;
				}

				if(i == o->angrate_axis){
					o->sol.ang_rate[i] = raw_sensor_data.gyro[o->angrate_axis];
				}
			}

			USER_OS_GIVE_MUTEX(o->mutex);
		}

		// Выдаче семафора внешней синхронизации
		if(o->extSync){
			USER_OS_GIVE_BIN_SEMAPHORE(o->extSync);
		}
	}
}

bool ImuFilter::init(void){
	mutex = USER_OS_STATIC_MUTEX_CREATE(&mutexBuff);
	extSync = USER_OS_STATIC_BIN_SEMAPHORE_CREATE(&extSyncBuff);
	USER_OS_STATIC_TASK_CREATE( imuThread, "mpuTask", TASK_STACK_SIZES, this, 4, this->p_stack, &this->p_struct );
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

/*
 * Реализация интерфейса
 */

bool ImuFilter::isReadyToWork(void){
	return inited;
}

bool ImuFilter::getSol(imu_sol_t &sol){
	bool rv = false;
	if(USER_OS_TAKE_MUTEX(mutex, portMAX_DELAY) == pdTRUE){
		sol = this->sol;
		rv = true;
		USER_OS_GIVE_MUTEX(mutex);
	}
	return rv;
}

bool ImuFilter::getSolBlocked(imu_sol_t &sol){
	bool rv = false;
	if(USER_OS_TAKE_SEMAPHORE(extSync, portMAX_DELAY) == pdTRUE){
		if(USER_OS_TAKE_MUTEX(mutex, portMAX_DELAY) == pdTRUE){
			sol = this->sol;
			rv = true;
			USER_OS_GIVE_MUTEX(mutex);
		}
	}
	return rv;
}
