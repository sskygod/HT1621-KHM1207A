#include <stdint.h>

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

class HT1621
{
    public:
        HT1621();
        HT1621(uint8_t cs_pin, uint8_t wr_pin, uint8_t data_pin);

        void send_cmd(uint16_t command_code);
        void send_data(uint8_t segment, uint8_t val);
        void clear_ram(void);

    private:
        uint8_t cs_pin_def;
        uint8_t wr_pin_def;
        uint8_t data_pin_def;

        void send(uint16_t data, uint8_t len);
        void config();

};
