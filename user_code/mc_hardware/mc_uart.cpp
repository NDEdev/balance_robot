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
		.uart = USART1,
		.baudrate = 1000000,
		.mode = UART_MODE_TX_RX,
		.dmaTx = DMA1_Stream3,
		.dmaTxCh = DMA_CHANNEL_3
};

Uart uartObj(&uartCfg, 1);
