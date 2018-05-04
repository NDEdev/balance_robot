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
#include "mpu_hw_interface.h"
#include "mc_hardware_interfaces_spi.h"




class Mpu6500: public Mpu::MpuInterface{

#define	TASK_STACK_SIZES		300

	bool 									inited = false;
	USER_OS_STATIC_BIN_SEMAPHORE			sync;
	USER_OS_STATIC_BIN_SEMAPHORE			mutex;

	USER_OS_STATIC_BIN_SEMAPHORE_BUFFER		syncBuff;
	USER_OS_STATIC_BIN_SEMAPHORE_BUFFER		mutexBuff;

	USER_OS_STATIC_STACK_TYPE 				p_stack[TASK_STACK_SIZES];
	USER_OS_STATIC_TASK_STRUCT_TYPE			p_struct;

	static void 	mpuThread		(void *p);

public:
	Mpu6500							(SpiMaster8BitBase *_spi);
	 ~Mpu6500();
	 SpiMaster8BitBase 					*spi ;

	bool					init();

	bool				getSolBlocked		(Mpu::mpu_sol_t &sol);
	bool 				isReadyToWork		();

};

#endif

#endif /* USER_CODE_MPU6500_H_ */
