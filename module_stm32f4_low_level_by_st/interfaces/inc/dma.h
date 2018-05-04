#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_rcc.h"

#ifdef __cplusplus
extern "C" {
#endif

void dmaClkOn ( DMA_Stream_TypeDef* dma);
void dmaIrqOn ( DMA_Stream_TypeDef* dma, uint32_t prio );

#ifdef __cplusplus
}
#endif
