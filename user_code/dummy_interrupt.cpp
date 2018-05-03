extern "C" {

void	NMI_Handler						( void )	{ while( true ); }
void	HardFault_Handler				( void )	{ while( true ); }
void	MemManage_Handler				( void )	{ while( true ); }
void	BusFault_Handler				( void )	{ while( true ); }
void	UsageFault_Handler				( void )	{ while( true ); }
void	DebugMon_Handler				( void )	{ while( true ); }


__attribute__((weak))  void	WWDG_IRQHandler					( void )	{ while( true ); }
__attribute__((weak))  void	PVD_IRQHandler					( void )	{ while( true ); }
__attribute__((weak))  void	TAMP_STAMP_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	RTC_WKUP_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	FLASH_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	RCC_IRQHandler					( void )	{ while( true ); }
__attribute__((weak))  void	EXTI0_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	EXTI1_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	EXTI2_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	EXTI3_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	EXTI4_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	DMA1_Stream0_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	DMA1_Stream1_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	DMA1_Stream2_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	DMA1_Stream3_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	DMA1_Stream4_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	DMA1_Stream5_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	DMA1_Stream6_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	ADC_IRQHandler					( void )	{ while( true ); }
__attribute__((weak))  void	CAN1_TX_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	CAN1_RX0_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	CAN1_RX1_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	CAN1_SCE_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	EXTI9_5_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	TIM1_BRK_TIM9_IRQHandler		( void )	{ while( true ); }
__attribute__((weak))  void	TIM1_UP_TIM10_IRQHandler		( void )	{ while( true ); }
__attribute__((weak))  void	TIM1_TRG_COM_TIM11_IRQHandler	( void )	{ while( true ); }
__attribute__((weak))  void	TIM1_CC_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	TIM2_IRQHandler					( void )	{ while( true ); }
__attribute__((weak))  void	TIM3_IRQHandler					( void )	{ while( true ); }
__attribute__((weak))  void	TIM4_IRQHandler					( void )	{ while( true ); }
__attribute__((weak))  void	I2C1_EV_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	I2C1_ER_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	I2C2_EV_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	I2C2_ER_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	SPI1_IRQHandler					( void )	{ while( true ); }
__attribute__((weak))  void	SPI2_IRQHandler					( void )	{ while( true ); }
__attribute__((weak))  void	USART1_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	USART2_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	USART3_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	EXTI15_10_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	RTC_Alarm_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	OTG_FS_WKUP_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	TIM8_BRK_TIM12_IRQHandler		( void )	{ while( true ); }
__attribute__((weak))  void	TIM8_UP_TIM13_IRQHandler		( void )	{ while( true ); }
__attribute__((weak))  void	TIM8_TRG_COM_TIM14_IRQHandler	( void )	{ while( true ); }
__attribute__((weak))  void	TIM8_CC_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	DMA1_Stream7_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	FSMC_IRQHandler					( void )	{ while( true ); }
__attribute__((weak))  void	SDIO_IRQHandler					( void )	{ while( true ); }
__attribute__((weak))  void	TIM5_IRQHandler					( void )	{ while( true ); }
__attribute__((weak))  void	SPI3_IRQHandler					( void )	{ while( true ); }
__attribute__((weak))  void	UART4_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	UART5_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	TIM7_IRQHandler					( void )	{ while( true ); }
__attribute__((weak))  void	DMA2_Stream0_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	DMA2_Stream1_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	DMA2_Stream2_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	DMA2_Stream3_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	DMA2_Stream4_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	ETH_IRQHandler					( void )	{ while( true ); }
__attribute__((weak))  void	ETH_WKUP_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	CAN2_TX_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	CAN2_RX0_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	CAN2_RX1_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	CAN2_SCE_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	OTG_FS_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	DMA2_Stream5_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	DMA2_Stream6_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	DMA2_Stream7_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	USART6_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	I2C3_EV_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	I2C3_ER_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	OTG_HS_EP1_OUT_IRQHandler		( void )	{ while( true ); }
__attribute__((weak))  void	OTG_HS_EP1_IN_IRQHandler		( void )	{ while( true ); }
__attribute__((weak))  void	OTG_HS_WKUP_IRQHandler			( void )	{ while( true ); }
__attribute__((weak))  void	OTG_HS_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	DCMI_IRQHandler					( void )	{ while( true ); }
__attribute__((weak))  void	HASH_RNG_IRQHandler				( void )	{ while( true ); }
__attribute__((weak))  void	FPU_IRQHandler					( void )	{ while( true ); }


}
