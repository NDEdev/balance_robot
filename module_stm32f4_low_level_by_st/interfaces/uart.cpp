#include "uart.h"

Uart::Uart( const uartCfg* const cfg ) : cfg(cfg) {
	this->handle.Instance							= cfg->UARTx;

	this->handle.Init.BaudRate						= cfg->baudrate;
	this->handle.Init.HwFlowCtl						= UART_HWCONTROL_NONE;
	this->handle.Init.Mode							= cfg->mode;
	this->handle.Init.OverSampling					= UART_OVERSAMPLING_8;
	this->handle.Init.Parity						= UART_PARITY_NONE;
	this->handle.Init.StopBits						= UART_STOPBITS_1;
	this->handle.Init.WordLength					= UART_WORDLENGTH_8B;

	if ( cfg->dmaTx != nullptr ) {
		this->handle.hdmatx = &this->hdmaTx;
		this->handle.hdmatx->Instance					= this->cfg->dmaTx;
		this->handle.hdmatx->Init.Channel				= this->cfg->dmaTxCh;
		this->handle.hdmatx->Init.Direction				= DMA_MEMORY_TO_PERIPH;
		this->handle.hdmatx->Init.PeriphInc				= DMA_PINC_DISABLE;
		this->handle.hdmatx->Init.MemInc				= DMA_MINC_ENABLE;
		this->handle.hdmatx->Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE;
		this->handle.hdmatx->Init.MemDataAlignment		= DMA_MDATAALIGN_BYTE;
		this->handle.hdmatx->Init.Mode					= DMA_NORMAL;
		this->handle.hdmatx->Init.Priority				= DMA_PRIORITY_HIGH;
		this->handle.hdmatx->Init.FIFOMode				= DMA_FIFOMODE_DISABLE;

		this->handle.hdmatx                             = &this->hdmaTx;
		this->handle.hdmatx->Parent                     = &this->handle;
	}

	// Грязный хак. Сохраняем в структуру HAL-uart-а указатель на объект.
	this->handle.obj = this;

    this->m = USER_OS_STATIC_MUTEX_CREATE( &this->mb );
    this->s = USER_OS_STATIC_BIN_SEMAPHORE_CREATE( &this->sb );
}

bool Uart::reinit ( void ) const {
	init_clk();

	if ( cfg->dmaTx != nullptr ) {
		dma_clk_on( this->cfg->dmaTx );
		dma_irq_on( this->cfg->dmaTx, this->cfg->handlerPrio );
	}

	HAL_StatusTypeDef r;
	r = HAL_UART_DeInit( &this->handle );
	if ( r != HAL_OK ) return false;

	r = HAL_UART_Init( &this->handle );
	if ( r != HAL_OK ) return false;

	return true;
}

void Uart::on ( void ) const {
	__HAL_UART_ENABLE( &this->handle );
}

void Uart::off ( void ) const {
	__HAL_UART_DISABLE( &this->handle );
}

BASE_RESULT Uart::tx ( const uint8_t* const  p_array_tx, const uint16_t& length, const uint32_t& timeout_ms ) const {
    if ( this->m != nullptr)			USER_OS_TAKE_MUTEX( this->m, portMAX_DELAY );

	USER_OS_TAKE_BIN_SEMAPHORE ( this->s, 0 );

	if ( cfg->dmaTx != nullptr ) {												// Если передача идет по DMA.
		HAL_UART_Transmit_DMA( &this->handle, (uint8_t*)p_array_tx, length );
	} else {																	// Если по прерываниям.
		HAL_UART_Transmit_IT( &this->handle, (uint8_t*)p_array_tx, length );
	}

	volatile BASE_RESULT rv = BASE_RESULT::TIME_OUT;
	if ( USER_OS_TAKE_BIN_SEMAPHORE ( this->s, timeout_ms ) == pdTRUE ) {
		rv = BASE_RESULT::OK;
	}

    if ( this->m != nullptr)				USER_OS_GIVE_MUTEX( this->m );
	return rv;
}

BASE_RESULT Uart::getByte ( uint8_t* data ) const {
	*data = this->handle.Instance->DR;
	return BASE_RESULT::OK;
}

void Uart::irq_handler ( void ) const {
	HAL_UART_IRQHandler( &this->handle );
}

extern "C" {
void HAL_UART_TxCpltCallback( UART_HandleTypeDef *huart ) {
	((Uart*)huart->obj)->give_semaphore();
}
}

// Private.
void Uart::give_semaphore ( void ) const {
    if ( this->s ) {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		USER_OS_GIVE_BIN_SEMAPHORE_FROM_ISR ( this->s, &xHigherPriorityTaskWoken);
    }
}

bool Uart::init_clk ( void ) const {
    switch ( ( uint32_t )this->cfg->UARTx ) {
#ifdef USART1
        case    USART1_BASE:     __USART1_CLK_ENABLE();     break;
#endif
#ifdef USART2
        case    USART2_BASE:     __USART2_CLK_ENABLE();     break;
#endif
#ifdef USART3
        case    USART3_BASE:     __USART3_CLK_ENABLE();     break;
#endif
#ifdef UART4
        case	UART4_BASE:		__UART4_CLK_ENABLE();		break;
#endif
#ifdef UART5
        case	UART5_BASE:		__UART5_CLK_ENABLE();		break;
#endif
#ifdef UART6
        case	UART6_BASE:		__UART6_CLK_ENABLE();		break;
#endif
#ifdef UART7
        case	UART7_BASE:		__UART7_CLK_ENABLE();		break;
#endif
#ifdef UART8
        case	UART8_BASE:		__UART8_CLK_ENABLE();		break;
#endif
    };
    return true;
}
