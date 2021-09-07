#include "SPI_HAL.h"

#define ARDUINO 1

#ifdef ARDUINO
#include <SPI.h>

State spi_activate() 
{
    SPI.begin();
}

State spi_transfer(uint8_t* read_data_buffer, 
                    uint16_t read_len,
                    uint8_t* write_data_buffer,
                    uint16_t write_len) 
{
    uint16_t transfer_len = (read_len > write_len) ? read_len : write_len;
    
    uint16_t i = 0u;

    while (i < transfer_len)
    {
        uint8_t received_data = 0u;

        if (i < write_len) {
            received_data = SPI.transfer(write_data_buffer[i]);    
        }
        else {
            received_data = SPI.transfer(0u);
        }

        if (i < read_len) {
            read_data_buffer[i] = received_data;
        }
    }

    return State.success;
}

#elif ARM

State spi_transfer(uint8_t* read_data_buffer, 
                    uint16_t read_len,
                    uint8_t* write_data_buffer,
                    uint16_t write_len) {
}

#endif