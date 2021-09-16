/**
 * 
 * 
**/

#include <stdint.h>
#include <stdbool.h>

enum State {
    failed = 1,
    success = 0
};

enum Mode {
    dedicated_mode = 0,
    bitbang_mode = 1
};

class SPI_HAL
{
    public:
        SPI_HAL();
        SPI_HAL(uint8_t cs_pin, 
                uint8_t mosi_pin, 
                uint8_t miso_pin, 
                uint8_t clk_pin);

        uint8_t transfer(uint8_t* read_data_buffer, 
                    uint16_t read_len,
                    uint8_t* write_data_buffer,
                    uint16_t write_len);

    private:
        uint8_t cs_pin_def;
        uint8_t mosi_pin_def;
        uint8_t miso_pin_def;
        uint8_t clk_pin_def;
        bool initialized;
        uint8_t mode;

        void set_CS_low(void);
        void set_CS_high(void);

        uint8_t transfer_dedicated(uint8_t* read_data_buffer, 
                                uint16_t read_len,
                                uint8_t* write_data_buffer,
                                uint16_t write_len);
        uint8_t transfer_bitbang(uint8_t* read_data_buffer, 
                                uint16_t read_len,
                                uint8_t* write_data_buffer,
                                uint16_t write_len);

        uint8_t bitbang(uint8_t send_data);
};
           
