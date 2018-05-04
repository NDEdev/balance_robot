/*
 * mpu6500.cpp
 *
 *  Created on: May 3, 2018
 *      Author: demid
 */


#include "mpu6500.h"



Mpu6500::Mpu6500(SpiMaster8BitBase *_spi):  spi(_spi){

}

Mpu6500::~Mpu6500(){

}

bool Mpu6500::init(void){
	bool rv = false;

	if(!spi)
		return false;

	if(spi->reinit() == BASE_RESULT::OK){
		spi->on();
		rv = true;
		inited = true;
	}

	USER_OS_STATIC_TASK_CREATE( mpuThread, "mpuTask", TASK_STACK_SIZES, this, 3, this->p_stack, &this->p_struct );

	return rv;
}

void Mpu6500::mpuThread(void *p){
	Mpu6500 *d = (Mpu6500*) p;

	if(!d){
		configASSERT(d);
	}

	uint8_t data[3] = { 10, 15, 20};
	while(true){
		d->spi->tx(data, sizeof(data), 100);
		vTaskDelay(100);

	}
}

bool				Mpu6500::getSolBlocked		(Mpu::mpu_sol_t &sol){

}

bool 				Mpu6500::isReadyToWork 		(void){

}

