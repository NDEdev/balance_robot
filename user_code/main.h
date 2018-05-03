#pragma once

#include "stm32f4xx_hal.h"
#include "freertos_headers.h"
#include "user_os.h"
#include "port.h"
#include "pin.h"
#include "rcc.h"
#include "wdt.h"


#define TB_LED_TASK_SIZE				200
#ifdef __cplusplus
extern "C" {
#endif

int main ( void );

#ifdef __cplusplus
}
#endif
