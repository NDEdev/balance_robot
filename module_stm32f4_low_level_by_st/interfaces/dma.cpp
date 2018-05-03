#include "dma.h"

void dma_clk_on ( DMA_Stream_TypeDef* dma) {
    switch ( (uint32_t)dma ) {
    case DMA1_Stream0_BASE:
    case DMA1_Stream1_BASE:
    case DMA1_Stream2_BASE:
    case DMA1_Stream3_BASE:
    case DMA1_Stream4_BASE:
    case DMA1_Stream5_BASE:
    case DMA1_Stream6_BASE:
    case DMA1_Stream7_BASE:
        __HAL_RCC_DMA1_CLK_ENABLE();
        break;
    };

    switch ( (uint32_t)dma ) {
    case DMA2_Stream0_BASE:
    case DMA2_Stream1_BASE:
    case DMA2_Stream2_BASE:
    case DMA2_Stream3_BASE:
    case DMA2_Stream4_BASE:
    case DMA2_Stream5_BASE:
    case DMA2_Stream6_BASE:
    case DMA2_Stream7_BASE:
        __HAL_RCC_DMA2_CLK_ENABLE();
        break;
    };
}

void dma_irq_on ( DMA_Stream_TypeDef* dma, uint32_t prio ) {
    switch ( (uint32_t)dma ) {
	case DMA1_Stream0_BASE: NVIC_SetPriority( DMA1_Stream0_IRQn, prio );    NVIC_EnableIRQ( DMA1_Stream0_IRQn ); break;
	case DMA1_Stream1_BASE: NVIC_SetPriority( DMA1_Stream1_IRQn, prio );    NVIC_EnableIRQ( DMA1_Stream1_IRQn ); break;
	case DMA1_Stream2_BASE: NVIC_SetPriority( DMA1_Stream2_IRQn, prio );    NVIC_EnableIRQ( DMA1_Stream2_IRQn ); break;
	case DMA1_Stream3_BASE: NVIC_SetPriority( DMA1_Stream3_IRQn, prio );    NVIC_EnableIRQ( DMA1_Stream3_IRQn ); break;
	case DMA1_Stream4_BASE: NVIC_SetPriority( DMA1_Stream4_IRQn, prio );    NVIC_EnableIRQ( DMA1_Stream4_IRQn ); break;
	case DMA1_Stream5_BASE: NVIC_SetPriority( DMA1_Stream5_IRQn, prio );    NVIC_EnableIRQ( DMA1_Stream5_IRQn ); break;
	case DMA1_Stream6_BASE: NVIC_SetPriority( DMA1_Stream6_IRQn, prio );    NVIC_EnableIRQ( DMA1_Stream6_IRQn ); break;
	case DMA1_Stream7_BASE: NVIC_SetPriority( DMA1_Stream7_IRQn, prio );    NVIC_EnableIRQ( DMA1_Stream7_IRQn ); break;
    };

    switch ( (uint32_t)dma ) {
	case DMA2_Stream0_BASE: NVIC_SetPriority( DMA2_Stream0_IRQn, prio );    NVIC_EnableIRQ( DMA2_Stream0_IRQn ); break;
	case DMA2_Stream1_BASE: NVIC_SetPriority( DMA2_Stream1_IRQn, prio );    NVIC_EnableIRQ( DMA2_Stream1_IRQn ); break;
	case DMA2_Stream2_BASE: NVIC_SetPriority( DMA2_Stream2_IRQn, prio );    NVIC_EnableIRQ( DMA2_Stream2_IRQn ); break;
	case DMA2_Stream3_BASE: NVIC_SetPriority( DMA2_Stream3_IRQn, prio );    NVIC_EnableIRQ( DMA2_Stream3_IRQn ); break;
	case DMA2_Stream4_BASE: NVIC_SetPriority( DMA2_Stream4_IRQn, prio );    NVIC_EnableIRQ( DMA2_Stream4_IRQn ); break;
	case DMA2_Stream5_BASE: NVIC_SetPriority( DMA2_Stream5_IRQn, prio );    NVIC_EnableIRQ( DMA2_Stream5_IRQn ); break;
	case DMA2_Stream6_BASE: NVIC_SetPriority( DMA2_Stream6_IRQn, prio );    NVIC_EnableIRQ( DMA2_Stream6_IRQn ); break;
	case DMA2_Stream7_BASE: NVIC_SetPriority( DMA2_Stream7_IRQn, prio );    NVIC_EnableIRQ( DMA2_Stream7_IRQn ); break;
    };
}
