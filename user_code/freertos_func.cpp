#include <stdint.h>
#include "stm32f4xx_hal_conf.h"
#include "stm32f4xx_hal.h"
#include "timer.h"
#include "FreeRTOSConfig.h"

#ifdef configGENERATE_RUN_TIME_STATS
extern TimInterrupt		timRunTimeStatsInterruptObj;
uint32_t				runTimeCounterValue = 0;
#define GENERATE_RUN_TIME_TIME_HANDLER			TIM6_DAC_IRQHandler
#define GENERATE_RUN_TIME_TIME_IRQ_NAME			TIM6_DAC_IRQn
#endif

extern "C" {

extern void xPortSysTickHandler ( void );
void SysTick_Handler(void) {
	HAL_IncTick();
	xPortSysTickHandler();
}

#ifdef configGENERATE_RUN_TIME_STATS

void vConfigureTimerForRunTimeStats ( void ) {
	timRunTimeStatsInterruptObj.reinit();
	timRunTimeStatsInterruptObj.on();
	NVIC_SetPriority( GENERATE_RUN_TIME_TIME_IRQ_NAME,  6 );
	NVIC_EnableIRQ( GENERATE_RUN_TIME_TIME_IRQ_NAME );
}

uint32_t vGetRunTimeCounterValue ( void ) {
	return runTimeCounterValue;
}

void GENERATE_RUN_TIME_TIME_HANDLER ( void ) {
	runTimeCounterValue++;
	timRunTimeStatsInterruptObj.clearInterruptFlag();
}

#endif

}
