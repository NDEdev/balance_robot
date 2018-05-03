#pragma once

#include "dma.h"
#include "user_os.h"
#include "mc_hardware_interfaces_spi.h"
#include "pin.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_dma.h"

struct spiMaster8bitCfg {
	SPI_TypeDef*				SPIx;
	const PinBase*		   		pinCs;
	uint32_t					clkPolarity;					// SPI_Clock_Polarity.
	uint32_t					clkPhase;						// SPI_Clock_Phase.
	uint32_t					baudratePrescaler;				// SPI_BaudRate_Prescaler
// В случае, если DMA не используется (передача и прием на прерываниях),
// то следует указать nullptr.
	DMA_Stream_TypeDef*			dmaTx;							// Из мерии DMAx_Streamx.
	DMA_Stream_TypeDef*			dmaRx;							// Из мерии DMAx_Streamx.
	uint32_t					dmaTxCh;						// Из серии DMA_CHANNEL_x.
	uint32_t					dmaRxCh;						// Из серии DMA_CHANNEL_x.

	uint8_t						handlerPrio;					// 1, 2..15.
};

class spi_master_8bit : public spi_master_8bit_base {
public:
	spi_master_8bit( const spiMaster8bitCfg* const cfg );
	BASE_RESULT  reinit ( void ) const;
	void on	 ( void ) const;
	void off	( void ) const;
	BASE_RESULT tx ( const uint8_t* const  p_array_tx, const uint16_t& length, const uint32_t& timeout_ms, const SPI::STEP_MODE step_mode = SPI::STEP_MODE::INC ) const;
	BASE_RESULT tx ( const uint8_t* const  p_array_tx, uint8_t* p_array_rx, const uint16_t& length, const uint32_t& timeout_ms ) const;
	BASE_RESULT tx_one_item ( const uint8_t p_item_tx, const uint16_t count, const uint32_t timeout_ms ) const;
	BASE_RESULT rx ( uint8_t* p_array_rx, const uint16_t& length, const uint32_t& timeout_ms, const uint8_t& out_value = 0xFF ) const;
	BASE_RESULT set_prescaler ( uint32_t prescaler ) const;

	void	give_semaphore ( void );												// Отдать симафор из прерывания (внутренняя функция.

	void	handler ( void );

private:
	bool	init_clk_spi		( void ) const;										// Включаем тактирование SPI и DMA (если используется).
	bool	init_spi			( void ) const;										// Инициализируем только SPI (считается, что он уже затактирован).
	bool	init_spi_irq		( void ) const;										// Включаем нужные прерывания (по SPI (если нет DMA) иначе DMA).

	uint8_t							 				num_cfg;				   	// Колличество структур переинициализации.

	mutable SPI_HandleTypeDef			   			handle;

	mutable USER_OS_STATIC_BIN_SEMAPHORE_BUFFER	 	sb;
	mutable USER_OS_STATIC_BIN_SEMAPHORE				s = nullptr;

	uint8_t												runtime_flags	= 0;
	mutable DMA_HandleTypeDef							hdma_tx;
	mutable DMA_HandleTypeDef							hdma_rx;

	const spiMaster8bitCfg* const cfg;

	USER_OS_STATIC_MUTEX							m = nullptr;
	USER_OS_STATIC_MUTEX_BUFFER			 			mb;
};
