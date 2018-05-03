#pragma once

#include <stdint.h>

enum class RCC_RESULT {
    OK                  = 0,            // Операция успешна произведена.
    ERROR_CFG_NUMBER    = 1,
    ERROR_CLK_INIT      = 2,
    ERROR_OSC_INIT      = 3
};

class RccBase {
public:
    virtual RCC_RESULT setCfg ( uint32_t numberCfg = 0 ) const = 0;
};
