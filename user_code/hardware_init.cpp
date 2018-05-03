/*
 * hardware_init.cpp
 *
 *  Created on: May 3, 2018
 *      Author: demid
 */

#include "spi.h"
#include "mpu6500.h"

extern spi_master_8bit spi1;

void DMA2_Stream0_IRQHandler(void){
	spi1.handler();
}

void DMA2_Stream3_IRQHandler(void){
	spi1.handler();
}

Mpu6500	mpuObj(&spi1);

void hardware_init(void){
	if(!mpuObj.init() )
		configASSERT(0);

	NVIC_SetPriority( DMA2_Stream0_IRQn,  6 );
	NVIC_EnableIRQ( DMA2_Stream0_IRQn );
	NVIC_SetPriority( DMA2_Stream3_IRQn,  6 );
	NVIC_EnableIRQ( DMA2_Stream3_IRQn );


}
