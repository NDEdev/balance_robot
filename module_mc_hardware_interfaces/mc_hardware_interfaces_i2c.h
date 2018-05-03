#pragma once

#include <stdint.h>

#ifdef __cplusplus

class i2c_base {
public:
    virtual void reinit     ( void ) const = 0;

    virtual int read        ( uint8_t slave_addr, uint8_t* p_buf, uint8_t read_addr, uint16_t num_byte_to_readr ) const = 0;
    virtual int read_dma    ( uint8_t slave_addr, uint8_t* p_buf, uint8_t read_addr, uint16_t num_byte_to_readr ) const = 0;
    virtual int write_byte  ( uint8_t slave_addr, uint8_t* p_buf, uint8_t write_addr ) const = 0;
};

#endif
