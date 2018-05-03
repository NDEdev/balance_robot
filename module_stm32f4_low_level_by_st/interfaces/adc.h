#include "mc_hardware_interfaces_adc.h"
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_rcc.h"

struct AdcOneChannelCfg {
	ADC_TypeDef*		ADCx;
	uint32_t			clockPrescaler;								// ADC_ClockPrescaler
	uint32_t			resolution;									// ADC_Resolution
	uint32_t			dataAlign;									// ADC_Data_align
	uint32_t			channel;									// ADC_channels
	uint32_t			samplingTime;								// ADC_sampling_times
};

class AdcOneChannel : public AdcOneChannelBase {
public:
	AdcOneChannel( const AdcOneChannelCfg* const cfg );

	bool reinit							( void )								const;
	bool startContinuousConversion		( void )								const;
	bool stopContinuousConversion		( void )								const;
	void getMeasurement					( uint32_t& channel_measurement )		const;

	void clkEnable						( void )								const;
	void clkDisable						( void )								const;

private:
	mutable ADC_HandleTypeDef				adcSt;
	mutable ADC_ChannelConfTypeDef			channelCfg;
};
