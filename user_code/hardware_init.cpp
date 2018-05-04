/*
 * hardware_init.cpp
 *
 *  Created on: May 3, 2018
 *      Author: demid
 */

#include "spi.h"
#include "mpu6500.h"

extern SpiMaster8Bit spi1;

extern "C"{

void DMA2_Stream0_IRQHandler(void){
	spi1.irqHandler();
}

void DMA2_Stream3_IRQHandler(void){
	spi1.irqHandler();
}

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
