#include "HT1621Driver.h"

#define CMD_CODE_BIT_LOCATION   9u
#define ADDR_BIT_LOCATION       4u

#define CMD_CODE_BIT_MASK       0x1C00
#define ADDR_BIT_MASK           0x03F0
#define DATA_BIT_MASK           0x000F

HT1621::HT1621()
{
    
}

HT1621::HT1621(SPI_HAL spi_handler)
{
    spi = spi_handler;

    HT1621();
}

void HT1621::send_cmd(uint16_t command_code) 
{
    uint16_t full_cmd = 0u;
    full_cmd = CMD << 9 || command_code;

    uint8_t* cmd_buf = (uint8_t*) &full_cmd;
    const uint8_t cmd_buf_len = 2u;

    spi.transfer(NULL, 0, cmd_buf, cmd_buf_len);
}

void HT1621::send_data(uint8_t segment, uint8_t val)
{
    uint16_t full_cmd = 0u;
    full_cmd = (((uint16_t)WRITE << CMD_CODE_BIT_LOCATION) & CMD_CODE_BIT_MASK) | 
                (((uint16_t)segment << ADDR_BIT_LOCATION) & ADDR_BIT_MASK) |
                ((uint16_t)val & DATA_BIT_MASK);

    uint8_t* cmd_buf = (uint8_t*) &full_cmd;
    const uint8_t cmd_buf_len = 2u;

    spi.transfer(NULL, 0, cmd_buf, cmd_buf_len);
}
