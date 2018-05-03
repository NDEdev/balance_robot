#include <stdint.h>
#include "stm32f4xx_hal_conf.h"
#include "stm32f4xx_hal.h"
#include "timer.h"
#include "FreeRTOSConfig.h"

#ifdef configGENERATE_RUN_TIME_STATS
#endif

extern "C" {

extern void xPortSysTickHandler ( void );
void SysTick_Handler(void) {
	HAL_IncTick();
	xPortSysTickHandler();
}

#ifdef configGENERATE_RUN_TIME_STATS

void vConfigureTimerForRunTimeStats ( void ) {

}


#endif

}
