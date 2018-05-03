/*
 * mc_mpu.cpp
 *
 *  Created on: May 3, 2018
 *      Author: demid
 */


#include "spi.h"
#include "dma.h"

extern Pin spiMpuCs;

uint32_t baudratePrescalerSpi1 = SPI_BAUDRATEPRESCALER_128;

/// Конфигурация SPI для работы c mpu6500
const spiMaster8bitCfg spi1Cfg = {
	.SPIx						=	SPI1,

	.pinCs						=	&spiMpuCs,

	.clkPolarity				=	SPI_POLARITY_HIGH,
	.clkPhase					=	SPI_PHASE_2EDGE,

	.baudratePrescaler			=	baudratePrescalerSpi1,

	.dmaTx						=	DMA2_Stream3,
	.dmaRx						=	DMA2_Stream0,
	.dmaTxCh					=	DMA_CHANNEL_3,
	.dmaRxCh					=	DMA_CHANNEL_3
};

spi_master_8bit spi1( &spi1Cfg );
