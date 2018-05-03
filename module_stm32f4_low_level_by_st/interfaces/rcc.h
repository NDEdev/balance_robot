#include "mc_hardware_interfaces_rcc.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_flash.h"
#include <stdint.h>

struct rcc_cfg {
	  uint32_t OscillatorType;       /*!< The oscillators to be configured.
	                                      This parameter can be a value of @ref RCC_Oscillator_Type                   */

	  uint32_t HSEState;             /*!< The new state of the HSE.
	                                      This parameter can be a value of @ref RCC_HSE_Config                        */

	  uint32_t LSEState;             /*!< The new state of the LSE.
	                                      This parameter can be a value of @ref RCC_LSE_Config                        */

	  uint32_t HSIState;             /*!< The new state of the HSI.
	                                      This parameter can be a value of @ref RCC_HSI_Config                        */

	  uint32_t HSICalibrationValue;  /*!< The HSI calibration trimming value (default is RCC_HSICALIBRATION_DEFAULT).
	                                       This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x1F */

	  uint32_t LSIState;             /*!< The new state of the LSI.
	                                      This parameter can be a value of @ref RCC_LSI_Config                        */

	  RCC_PLLInitTypeDef PLL;        /*!< PLL structure parameters                                                    */

	  uint32_t SYSCLKSource;         /*!< The clock source (SYSCLKS) used as system clock.
	                                       This parameter can be a value of @ref RCC_System_Clock_Source    */

	  uint32_t AHBCLKDivider;        /*!< The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
	                                       This parameter can be a value of @ref RCC_AHB_Clock_Source       */

	  uint32_t APB1CLKDivider;       /*!< The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
	                                       This parameter can be a value of @ref RCC_APB1_APB2_Clock_Source */

	  uint32_t APB2CLKDivider;       /*!< The APB2 clock (PCLK2) divider. This clock is derived from the AHB clock (HCLK).
	                                       This parameter can be a value of @ref RCC_APB1_APB2_Clock_Source */

	  uint32_t                    f_latency;
};

class Rcc : public RccBase {
public:
    Rcc( const rcc_cfg* const array_cfg_st, const uint32_t number_cfg ) : array_cfg_st( array_cfg_st ), number_cfg( number_cfg ) {}
    RCC_RESULT setCfg ( uint32_t number_cfg_set ) const;

private:
    const rcc_cfg*              const array_cfg_st;
    const uint32_t              number_cfg;
};
