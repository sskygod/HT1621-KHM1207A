#include "KHM1207A.h"
#include "HT1621Driver.h"

#define START_MEM   0x00
#define END_MEM     0x1F

// cs to pin 13
// wr to pin 12
// Data to pin 14 //8
SPI_HAL spi;

HT1621 HT1621_driver;

KHM1207::KHM1207()
{
    spi = SPI_HAL(13, 12, 14, 4);

    HT1621_driver = HT1621(spi);

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
    HT1621_driver.send_data(0x00, 0b1111);

    /*
    uint8_t data = 0b1111;

    for (uint8_t addr = START_MEM, i < END_MEM; addr++) 
    {
        write_data(addr, data);

        delay(1000);
    }
    */
}

void KHM1207::clear(void)
{
    
}