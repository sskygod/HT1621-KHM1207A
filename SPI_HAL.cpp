#include "SPI_HAL.h"

#define ARDUINO 1

#ifdef ARDUINO
#include <SPI.h>

SPI_HAL::SPI_HAL() 
{
    initialized = false;

    SPI.begin(); // Initialize SPI - 4000000 Baud, MODE0 (default)

    mode = dedicated_mode;

    initialized = true;
}

SPI_HAL::SPI_HAL(uint8_t cs_pin, 
                uint8_t mosi_pin, 
                uint8_t miso_pin, 
                uint8_t clk_pin)
{
    initialized = false;

    cs_pin_def = cs_pin;
    mosi_pin_def = mosi_pin;
    miso_pin_def = miso_pin;
    clk_pin_def = clk_pin;

	pinMode(cs_pin_def, OUTPUT);
	pinMode(mosi_pin_def, OUTPUT);
	pinMode(miso_pin_def, INPUT);
	pinMode(clk_pin_def, OUTPUT);

    mode = bitbang_mode;

    initialized = true;
}

void SPI_HAL::set_CS_low(void)
{
    digitalWrite(cs_pin_def, LOW); // Activate the CS line (CS is active LOW)
}

void SPI_HAL::set_CS_high(void)
{
    digitalWrite(cs_pin_def, HIGH); // Deactivate the CS line (CS is active LOW)
}

uint8_t SPI_HAL::transfer(uint8_t* read_data_buffer, 
                    uint16_t read_len,
                    uint8_t* write_data_buffer,
                    uint16_t write_len) 
{
    if (mode == dedicated_mode) 
    {
        transfer_dedicated(read_data_buffer, read_len, write_data_buffer, write_len);
    } 
    else 
    {
        transfer_bitbang(read_data_buffer, read_len, write_data_buffer, write_len);
    }
}

uint8_t SPI_HAL::transfer_dedicated(uint8_t* read_data_buffer, 
                                    uint16_t read_len,
                                    uint8_t* write_data_buffer,
                                    uint16_t write_len)
{
    uint16_t transfer_len = (read_len > write_len) ? read_len : write_len;
    
    uint16_t i = 0u;

    // Enable CS
    set_CS_low();

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

    // Disable CS
    set_CS_high();

    return success;
}

uint8_t SPI_HAL::transfer_bitbang(uint8_t* read_data_buffer, 
                                uint16_t read_len,
                                uint8_t* write_data_buffer,
                                uint16_t write_len)
{
    uint16_t transfer_len = (read_len > write_len) ? read_len : write_len;
    
    uint16_t i = 0u;

    // Enable CS
    set_CS_low();

    while (i < transfer_len)
    {
        uint8_t received_data = 0u;

        if (i < write_len) 
        {
            received_data = bitbang(write_data_buffer[i]);
        }
        else 
        {
            received_data = bitbang(0u);
        }

        if (i < read_len) {
            read_data_buffer[i] = received_data;
        }
    }

    // Disable CS
    set_CS_high();

    return success;
}

uint8_t SPI_HAL::bitbang(uint8_t send_data)
{
    uint8_t received_data = 0u;

    // Bitbang
    for (uint8_t i = 0; i < 8u; i++) 
    {
        // Send SCK Low
        digitalWrite(clk_pin_def, LOW);
        delayMicroseconds(4u);

        if (send_data & 0x80)
        {
            // Send bit
            digitalWrite(mosi_pin_def, HIGH);
        }
        else 
        {
            // Send bit
            digitalWrite(mosi_pin_def, LOW);
        }

        received_data <<= 1u;
        received_data &= (miso_pin_def & 0x01);

        // Send SCK High
        digitalWrite(clk_pin_def, HIGH);
        delayMicroseconds(4u);
    }

    return received_data;
}

#elif ARM

State spi_transfer(uint8_t* read_data_buffer, 
                    uint16_t read_len,
                    uint8_t* write_data_buffer,
                    uint16_t write_len) {
}

#endif