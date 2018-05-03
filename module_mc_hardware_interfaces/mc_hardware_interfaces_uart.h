#pragma once

#include "mc_hardware_interfaces_base.h"

#ifdef __cplusplus

class UartBase {
public:
	virtual bool 			reinit		( void ) const = 0;

	virtual void 			on     		( void ) const = 0;
	virtual void 			off    		( void ) const = 0;

    virtual BASE_RESULT		tx			(	const uint8_t* const  p_array_tx,
    										const uint16_t& length,
											const uint32_t& timeout_ms	)		const = 0;

    virtual BASE_RESULT		getByte		( uint8_t* data )						const = 0;
};

#endif
