#include "SPI_HAL.h"

#define ARDUINO 1

static void set_CS_low(void);
static void set_CS_high(void);

#ifdef ARDUINO
#include <SPI.h>

const int CS_PIN = 7;

void set_CS_low(void)
{
    digitalWrite(CS_PIN, LOW); // Activate the CS line (CS is active LOW)
}

void set_CS_high(void)
{
    digitalWrite(CS_PIN, HIGH); // Deactivate the CS line (CS is active LOW)
}

State spi_activate() 
{
    SPI.begin(); // Initialize SPI - 4000000 Baud, MODE0 (default)

    pinMode(CS_PIN, OUTPUT); // The CS_PIN should remain in a high impedance state (INPUT)
}

State spi_deactive()
{
    SPI.end();

    pinMode(CS_Pin, INPUT); // Set CS_Pin to high impedance to allow pull-up to reset CS to inactive.
}

State spi_transfer(uint8_t* read_data_buffer, 
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

    set_CS_high();

    return State.success;
}

#elif ARM

State spi_transfer(uint8_t* read_data_buffer, 
                    uint16_t read_len,
                    uint8_t* write_data_buffer,
                    uint16_t write_len) {
}

#endif