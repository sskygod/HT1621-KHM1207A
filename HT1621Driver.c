#include "HT1621Driver.h"
#include "SPI_HAL.h"

/* Command ID List */
#define READ            0b110
#define WRITE           0b101
#define CMD             0b100

/* Command Code List */
#define SYS_DIS         0b000000000
#define SYS_EN          0b000000010
#define LCD_OFF         0b000000100
#define LCD_ON          0b000000110
#define TIMER_DIS       0b000001000
#define WDT_DIS         0b000001010
#define TIMER_EN        0b000001100
#define WDT_EN          0b000001110
#define TONE_ON         0b000010000
#define TONE_OFF        0b000010010
#define CLR_TIMER       0b000011000
#define CLR_WDT         0b000011100
#define XTAL_32K        0b000101000
#define RC_256K         0b000110000
#define EXT_256K        0b000111000
#define BIAS_1_2_COM_2  0b001000000
#define BIAS_1_2_COM_3  0b001001000
#define BIAS_1_2_COM_4  0b001010000
#define BIAS_1_3_COM_2  0b001000010
#define BIAS_1_3_COM_3  0b001001010
#define BIAS_1_3_COM_4  0b001010010
#define TONE_4K         0b010000000
#define TONE_2K         0b011000000
#define IRQ_DIS         0b100000000
#define IRQ_EN          0b100010000
#define F1              0b101000000
#define F2              0b101000010
#define F4              0b101000100
#define F8              0b101000110
#define F16             0b101001000
#define F32             0b101001010
#define F64             0b101001100
#define F128            0b101001110
#define TEST            0b111000000
#define NORMAL          0b111000110

static void send_command(uint8_t command_id, uint16_t command_code);

//  ================================
//  INTERNAL
//  ================================

void send_command(uint16_t command_id, uint16_t command_code) 
{
    uint16_t full_cmd = 0u;
    full_cmd = command_id << 9 || command_code;

    uint8_t* cmd_buf = (uint8_t*) &full_cmd;

    spi_transfer(NULL, 0, cmd_buf, 2);
}

//  ================================
//  EXTERNAL
//  ================================
void initialize()
{
    // activate spi
    spi_activate();

    // setup configuration

    // Set Bias and commons
    send_command(CMD, BIAS_1_2_COM_4);

    // Turn on bias generator
    send_command(CMD, LCD_ON);

    // Enable System
    send_command(CMD, SYS_EN);
}

void set_lcd_off() 
{
    send_command(CMD, LCD_OFF);
}

void set_lcd_on() 
{
    send_command(CMD, LCD_ON);
}

void set_bias_com(uint8_t bias_option, uint8_t com) 
{
    switch (bias_option)
    {
    case Bias_1_2:
        
        switch (com)
        {
        case Commons_2:
            send_command(CMD, BIAS_1_2_COM_2);
            break;

        case Commons_3:
            send_command(CMD, BIAS_1_2_COM_3);
            break;

        case Commons_4:
            send_command(CMD, BIAS_1_2_COM_4);
            break;
        
        default:
            send_command(CMD, BIAS_1_2_COM_4);
            break;
        }

        break;

    case Bias_1_3:

        switch (com)
        {
        case Commons_2:
            send_command(CMD, BIAS_1_3_COM_2);
            break;

        case Commons_3:
            send_command(CMD, BIAS_1_3_COM_3);
            break;

        case Commons_4:
            send_command(CMD, BIAS_1_3_COM_4);
            break;
        
        default:
            send_command(CMD, BIAS_1_3_COM_4);
            break;
        }       

        break;
    
    default:
        send_command(CMD, BIAS_1_3_COM_4);
        break;
    }
}