#include <Arduino.h>
#include "KHM1207A.h"
#include "HT1621Driver.h"

#define BLANK_NUM   0x00

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

void KHM1207::run_demo(void)
{
    /*
    clear();

    HT1621_driver.send_data(0x00, 0b1000);

    delay(2000);

    clear();

    HT1621_driver.send_data(0x00, 0b0100);

    delay(2000);

    clear();

    HT1621_driver.send_data(0x00, 0b0010);

    delay(2000);

    clear();

    HT1621_driver.send_data(0x00, 0b0001);
    */
    HT1621_driver.clear_ram();

    set_number(5, 0);
    set_number(6, 1);
    set_number(7, 2);
    set_number(8, 3);
}

void KHM1207::set_number(uint8_t value, uint8_t location)
{
    uint8_t segment = location * 2u;

    HT1621_driver.send_data(segment, number_map[value]);
}

void KHM1207::set_dot(uint8_t location)
{

}