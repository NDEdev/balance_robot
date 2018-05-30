/*
 * mc_uart.cpp
 *
 *  Created on: May 17, 2018
 *      Author: demid
 */


#include "uart.h"


/*
 * UART для взаимодействия с RaspberyPi в части телеметрии и управления
 */
const uartCfg uartCfg= {
		.uart				=	USART1,
		.baudrate			=	115200,
		.mode				=	UART_MODE_TX_RX,
		.dmaTx				=	DMA2_Stream7,
		.dmaTxCh			=	DMA_CHANNEL_4
};

Uart uartObj(&uartCfg, 1);
