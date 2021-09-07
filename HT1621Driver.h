#include <stdint.h>

enum bias {
    Bias_1_2,
    Bias_1_3
}

enum com {
    Commons_2,
    Commons_3,
    Commons_4,
}

extern void initialize();

extern void set_lcd_off();
extern void set_lcd_on();
extern void set_bias_com(uint8_t bias_option, uint8_t com);

extern void read_data(uint8_t address, uint8_t* data);
extern void read_successive_data(uint8_t address, uint8_t* data, uint8_t len);

extern void write_data(uint8_t address, uint8_t data);
extern void write_successive_data(uint8_t address, uint8_t* data, uint8_t len);

/* read-modify-write */
extern void rmw_data(uint8_t address, uint8_t* r_data, uint8_t w_data);
extern void rmw_successive_data(uint8_t address, uint8_t* r_data, uint8_t w_data, uint8_t len);