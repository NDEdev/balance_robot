/*
 * hardware_init.cpp
 *
 *  Created on: May 3, 2018
 *      Author: demid
 */


//	MPU

#include "spi.h"
#include "mpu6500.h"

extern SpiMaster8Bit spi1;

Mpu6500	mpuObj(&spi1);

extern "C"{

void DMA2_Stream0_IRQHandler(void){
	spi1.irqHandler();
}

void DMA2_Stream3_IRQHandler(void){
	spi1.irqHandler();
}

void EXTI4_IRQHandler(void){
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_4) != RESET)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
		mpuObj.solutionReadyIrqHandler();
		taskYIELD();
	}
}

}

void hardware_init(void){
	if(!mpuObj.init() )
		configASSERT(0);

	NVIC_SetPriority( DMA2_Stream0_IRQn,  6 );
	NVIC_EnableIRQ( DMA2_Stream0_IRQn );
	NVIC_SetPriority( DMA2_Stream3_IRQn,  6 );
	NVIC_EnableIRQ( DMA2_Stream3_IRQn );
	NVIC_SetPriority( EXTI4_IRQn,  6 );
	NVIC_EnableIRQ( EXTI4_IRQn );

}
