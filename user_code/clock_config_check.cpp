/*
 * clock_config_check.cpp
 *
 *  Created on: May 3, 2018
 *      Author: demid
 */
#include "timer.h"
#include "pin.h"

extern TimInterrupt		tim9Irq;
extern TimInterrupt		tim2Irq;
extern Pin 				tim2Obj;
extern Pin 				tim9Obj;


extern "C" {

void TIM1_BRK_TIM9_IRQHandler(void){
	tim9Obj.toggle();
	tim9Irq.clearInterruptFlag();
}

void TIM2_IRQHandler(void){
	tim2Obj.toggle();
	tim2Irq.clearInterruptFlag();
}


/*!
 * Данная сущность предназначена для проверки правильности настройки
 * тактироавния на шинах APB1, APB2 с помощью таймера, gpio, и логического анализатора
 * настройки таймера должны соответствовать периоду в 1 с. Этот период нужно наблыюать на соостветвующей gpioлогическим анализатором
 *
 */
void clock_config_check_init(void){
/*
	uint32_t sys = HAL_RCC_GetSysClockFreq();
	uint32_t hcl = HAL_RCC_GetHCLKFreq();
	uint32_t apb1 = HAL_RCC_GetPCLK1Freq();
	uint32_t apb2 = HAL_RCC_GetPCLK2Freq();
*/
	//
	tim9Irq.reinit();
	tim9Irq.on();
	NVIC_SetPriority( TIM1_BRK_TIM9_IRQn,  6 );
	NVIC_EnableIRQ( TIM1_BRK_TIM9_IRQn );

	tim2Irq.reinit();
	tim2Irq.on();
	NVIC_SetPriority( TIM2_IRQn,  6 );
	NVIC_EnableIRQ( TIM2_IRQn );

}

}
