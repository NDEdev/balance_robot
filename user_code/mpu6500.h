/*
 * mpu6500.h
 *
 *  Created on: May 3, 2018
 *      Author: demid
 */

#ifndef USER_CODE_MPU6500_H_
#define USER_CODE_MPU6500_H_

#ifdef __cplusplus

#include "user_os.h"
#include "imu_sensor_interface.h"
#include "mc_hardware_interfaces_spi.h"

typedef struct{
	int16_t offset_x;
	int16_t offset_y;
	int16_t offset_z;
}mpu6500_offsets_t;


class Mpu6500: public Imu::ImuSensorInterface{

	#define	TASK_STACK_SIZES		300
	//Диапазон измерения акселерометра (+/- g) 2, 4, 8, 16
	#define ACCEL_RANGE 2
	//Диапазон измерения гироскопа (+/- dps) 250, 500, 1000, 2000
	#define GYRO_RANGE 500

	#define MPU6500_TEMP_SENSIVITY		333.87
	#define MPU6500_TEMP_OFFSET			0.0

	bool 									inited;
	USER_OS_STATIC_BIN_SEMAPHORE			sync;
	USER_OS_STATIC_BIN_SEMAPHORE			mutex;
	USER_OS_STATIC_BIN_SEMAPHORE			extSync; // семафор синхронизации внешнего потока

	USER_OS_STATIC_BIN_SEMAPHORE_BUFFER		syncBuff;
	USER_OS_STATIC_BIN_SEMAPHORE_BUFFER		extSyncBuff;
	USER_OS_STATIC_BIN_SEMAPHORE_BUFFER		mutexBuff;

	USER_OS_STATIC_STACK_TYPE 				p_stack[TASK_STACK_SIZES];
	USER_OS_STATIC_TASK_STRUCT_TYPE			p_struct;

	float gyro_scale;
	float acc_scale;
	uint8_t accel_config;
	uint8_t accel_config2;
	uint8_t int_status;
	uint8_t int_enable;
	bool calibration_enable;

	//Raw data
	int16_t accelGyroRaw[6];

	// Solution
	float accel[3];
	float gyro[3];
	float tempr;
	TickType_t dt;

	static void 		mpuThread			(void *p);

	bool				data_read			(void *buf, uint8_t addr, int l);
	bool				data_write			(void *buf, uint8_t addr, int l);
	bool				set_range			(int acell_range, int gyro_range, uint8_t fchoice_b );
	bool 				set_accel_offsets	(int16_t x_offser, int16_t y_offset, int16_t z_offset);
	bool 				set_gyro_offsets	(int16_t x_offser, int16_t y_offset, int16_t z_offset);
	bool 				read_offsets		(uint8_t addr, mpu6500_offsets_t *d);

public:
	Mpu6500							(SpiMaster8BitBase *_spi);
	 ~Mpu6500();
	 SpiMaster8BitBase 					*spi ;

	bool				init();
	void 				solutionReadyIrqHandler		(void); // Метод вызывается в прерывании GPIO solReady

	///Реализация интерфейса
	bool				getSolBlocked				(Imu::imu_sol_t &sol);
	bool				getSol						(Imu::imu_sol_t &sol);
	bool 				isReadyToWork				();

};

#endif

#endif /* USER_CODE_MPU6500_H_ */
