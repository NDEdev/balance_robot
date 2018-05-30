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

// ADC
#include "adc.h"
extern AdcOneChannel adcLeft;
extern AdcOneChannel adcRight;

// Current sensor
#include "current_sensor.h"
CurrentSensor currentSensorLeft		(&adcLeft, 1.0/0.082, 0.6, 5);
CurrentSensor currentSensorRight	(&adcRight, 1.0/0.082, 0.6, 5);

// PWM
#include "timer.h"
extern TimPwmOneChannel motorLeftPwm;
extern TimPwmOneChannel motorRightPwm;

// Motor driver
#include "motor_driver.h"

extern Pin mlEn;
extern Pin mlDir;
MotorDriver motorDriverLeft	(&currentSensorLeft, &motorLeftPwm, &mlEn, &mlDir, 1000);

extern Pin mrEn;
extern Pin mrDir;
MotorDriver motorDriverRight (&currentSensorRight, &motorRightPwm, &mrEn, &mrDir, 1000);

// TIM capture


// TIM Encoder


extern "C"{
/*
 * IMU
 */
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

/*
 * ADC Не требует обработчика прерывания
 */

/*
 * Current sensor не требует обработчика прерывания
 */

/*
 * PWM не требует обработчика прерывания
 */

}

void hardware_init(void){

	// IMU - MPU6500
	if(!mpuObj.init() )
		configASSERT(0);

	NVIC_SetPriority( DMA2_Stream0_IRQn,  6 );
	NVIC_EnableIRQ( DMA2_Stream0_IRQn );
	NVIC_SetPriority( DMA2_Stream3_IRQn,  6 );
	NVIC_EnableIRQ( DMA2_Stream3_IRQn );
	NVIC_SetPriority( EXTI4_IRQn,  6 );
	NVIC_EnableIRQ( EXTI4_IRQn );

	//ADC
	if(adcLeft.reinit() != BASE_RESULT::OK)
		configASSERT(0);

	adcLeft.startContinuousConversion();

	if(adcRight.reinit() != BASE_RESULT::OK)
			configASSERT(0);

	adcRight.startContinuousConversion();
	// Проверка

	//Current sensor инициализирован при создании объекта
	// проверка

	// PWM left motor
	if(motorLeftPwm.reinit(0) != BASE_RESULT::OK)
		configASSERT(0);

	// PWM right motor
	if(motorRightPwm.reinit(0) != BASE_RESULT::OK)
		configASSERT(0);

	//if(motorRightPwm.on() != BASE_RESULT::OK)
	//	configASSERT(0);

	//проверка

	// Motor driver left
	//if(!motorDriverLeft.init())
//		configASSERT(0);

	// Motor driver right
	//if(!motorDriverRight.init())
	//	configASSERT(0);

	//проверка

}
