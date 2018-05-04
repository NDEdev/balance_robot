#include "port.h"

#include "stm32f4xx_hal_gpio.h"

BASE_RESULT GlobalPort::reinitAllPorts ( void ) {
    for ( uint32_t l = 0; l < this->countCfg; l++ ) {
		gpioClkEn( (const GPIO_TypeDef*)this->cfg[l].GPIOx );
        HAL_GPIO_Init( ( GPIO_TypeDef* )cfg[l].GPIOx, ( GPIO_InitTypeDef* ) ( &cfg[l].init ) );
    }
	return BASE_RESULT::OK;
}
