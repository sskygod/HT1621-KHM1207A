/**
 * 
 * 
**/

#include <stdint.h>

enum State {
    failed = 1,
    success = 0,
};

extern State spi_activate();

extern State spi_deactivate();

extern State spi_transfer(uint8_t* read_data_buffer, 
                    uint16_t read_len
                    uint8_t* write_data_buffer
                    uint16_t write_len);

            
