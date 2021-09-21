#include <Arduino.h>
#include "KHM1207A.h"
#include "HT1621Driver.h"

#define FIRST_SEGMENT   0x00
#define LAST_SEGMENT    0x1F

#define BLANK_DIGIT     0x00

/* Number decode */
uint8_t number_map[10] = {
    0xEB,   // 0
    0x0A,   // 1
    0xAD,   // 2
    0x8F,   // 3
    0x4E,   // 4
    0xC7,   // 5
    0xE7,   // 6
    0x8A,   // 7
    0xEF,   // 8
    0xCF    // 9
};

// cs to pin 13
// wr to pin 12
// Data to pin 14 //8
HT1621 HT1621_driver;

KHM1207::KHM1207()
{
    HT1621_driver = HT1621(13, 12, 14);

    // Setup Bias
    HT1621_driver.send_cmd(BIAS_1_3_COM_4);
    // Setup RC256
    HT1621_driver.send_cmd(RC_256K);
    // Disable system
    HT1621_driver.send_cmd(SYS_DIS);
    // Disable WDT time-out flag output
    HT1621_driver.send_cmd(WDT_DIS);
    // Enable system again
    HT1621_driver.send_cmd(SYS_EN);
    // Turn on LCD bias generator
    HT1621_driver.send_cmd(LCD_ON);
}

bool KHM1207::set_number(uint16_t value)
{
    if (value > 9999) 
    {
        return false;
    }

    buffer[0] = value / 1000;

    uint16_t remainder = value % 1000;
    buffer[1] = remainder / 100;

    remainder %= 100;
    buffer[2] = remainder / 10;

    remainder %= 10;
    buffer[3] = remainder;

    // clear before update new data
    HT1621_driver.clear_ram();

    // encode
    for (uint8_t i = 0u; i < BUFFER_LEN; i++)
    {
        buffer[i] = number_map[buffer[i]];
    }

    // send bulk
    HT1621_driver.send_successive_data(FIRST_SEGMENT, buffer, BUFFER_LEN);

    return true;
}

bool KHM1207::set_digit(uint8_t location, uint8_t value)
{
    if (location > 4 || value > 9)
    {
        return false;
    }

    // Get current state of Dot or Colon
    uint8_t dot_colon = buffer[location] & 0b00010000;

    // convert to digit code then store (including previous state Dot or Colon)
    buffer[location] = dot_colon | number_map[value];

    // set segment
    uint8_t segment = location * 2u;

    HT1621_driver.send_data(segment, buffer[location]);

    return true;
}

bool KHM1207::set_dot(uint8_t location, bool state)
{
    if (location > 3)
    {
        return false;
    }

    if (state == true)
    {
        buffer[location + 1] |= 0b00010000;
    }
    else
    {
        buffer[location + 1] &= 0b11101111;
    }

    // set segment
    uint8_t segment = location * 2u;

    HT1621_driver.send_data(segment, buffer[location + 1]);

    return true;
}

void KHM1207::set_colon(bool state)
{
    const uint8_t segment = 0u;

    if (state == true)
    {
        buffer[0] |= 0b00010000;
    }
    else
    {
        buffer[0] &= 0b11101111;
    }   

    HT1621_driver.send_data(segment, buffer[0]);
}

