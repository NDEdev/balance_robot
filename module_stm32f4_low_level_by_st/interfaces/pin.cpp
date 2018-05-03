#include "pin.h"

void gpio_clk_en (  const GPIO_TypeDef* GPIOx ) {
    switch ( (uint32_t)GPIOx ) {
#ifdef GPIOA
        case GPIOA_BASE: __HAL_RCC_GPIOA_CLK_ENABLE(); break;
#endif

#ifdef GPIOB
        case GPIOB_BASE: __HAL_RCC_GPIOB_CLK_ENABLE(); break;
#endif

#ifdef GPIOC
        case GPIOC_BASE: __HAL_RCC_GPIOC_CLK_ENABLE(); break;
#endif

#ifdef GPIOD
        case GPIOD_BASE: __HAL_RCC_GPIOD_CLK_ENABLE(); break;
#endif

#ifdef GPIOE
        case GPIOE_BASE: __HAL_RCC_GPIOE_CLK_ENABLE(); break;
#endif

#ifdef GPIOF
        case GPIOF_BASE: __HAL_RCC_GPIOF_CLK_ENABLE(); break;
#endif

#ifdef GPIOG
        case GPIOG_BASE: __HAL_RCC_GPIOG_CLK_ENABLE(); break;
#endif

#ifdef GPIOH
        case GPIOH_BASE: __HAL_RCC_GPIOH_CLK_ENABLE(); break;
#endif
    }
}

void Pin::init ( void ) const {
    gpio_clk_en( this->cfg->GPIOx );
    HAL_GPIO_Init( ( GPIO_TypeDef* )this->cfg->GPIOx, ( GPIO_InitTypeDef * )this->cfg );
}

void Pin::set ( void ) const {
    HAL_GPIO_WritePin ( ( GPIO_TypeDef* )this->cfg->GPIOx, ( uint16_t )this->cfg->init.Pin, GPIO_PIN_SET);
}

void Pin::reset ( void ) const {
    HAL_GPIO_WritePin ( ( GPIO_TypeDef* )this->cfg->GPIOx, ( uint16_t )this->cfg->init.Pin, GPIO_PIN_RESET);
}

void Pin::toggle ( void ) const {
    HAL_GPIO_TogglePin ( ( GPIO_TypeDef* )this->cfg->GPIOx, ( uint16_t )this->cfg->init.Pin );
}

void Pin::set ( bool state ) const {
    if ( state ) {
        this->set();
    } else {
        this->reset();
    }
}

void Pin::set ( int state ) const {
    this->set( static_cast< bool >( state ) );
}

void Pin::set ( uint8_t state ) const {
    this->set( static_cast< bool >( state ) );
}

bool Pin::read ( void ) const {
    return HAL_GPIO_ReadPin ( ( GPIO_TypeDef* )this->cfg->GPIOx, ( uint16_t )this->cfg->init.Pin );
}
