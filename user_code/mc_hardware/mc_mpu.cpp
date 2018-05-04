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
const SpiMaster8BitCfg spi1Cfg = {
	.SPIx						=	SPI1,

	.pinCs						=	&spiMpuCs,

	.clkPolarity				=	SPI_POLARITY_HIGH,
	.clkPhase					=	SPI_PHASE_2EDGE,

	.baudratePrescalerArray		=	&baudratePrescalerSpi1,
	.numberBaudratePrescalerCfg = 	1,

	.dmaTx						=	DMA2_Stream3,
	.dmaRx						=	DMA2_Stream0,
	.dmaTxCh					=	DMA_CHANNEL_3,
	.dmaRxCh					=	DMA_CHANNEL_3
};

SpiMaster8Bit spi1( &spi1Cfg, 1 );
