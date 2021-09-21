#include <stdint.h>

#ifndef KHM1207A_H
#define KHM1207A_H

class KHM1207
{
    public:
        KHM1207();

        bool set_number(uint16_t value);
        bool set_digit(uint8_t location, uint8_t value);
        bool set_dot(uint8_t location, bool state);
        void set_colon(bool state);

        void update(void);

    private:
        uint8_t buffer[4];
};

#endif /* KHM1207A_H */