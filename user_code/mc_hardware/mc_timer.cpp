#include "timer.h"
#include "stm32f4xx_hal.h"
#include "FreeRTOSConfig.h"

#ifdef configGENERATE_RUN_TIME_STATS

clkTimBaseCfg		tim6BaseCfg = {
	.period					=	800 - 1,
	.prescaler				=	0,
	.pulse					=	0
};

TimInterruptCfg		timRunTimeStatsInterruptCfg = {
	.tim					= TIM6,
	.p_cfg					= &tim6BaseCfg,
	.size_cfg				= 1
};

TimInterrupt		timRunTimeStatsInterruptObj( &timRunTimeStatsInterruptCfg );

#endif
