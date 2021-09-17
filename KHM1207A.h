#include <stdint.h>

#ifndef KHM1207A_H
#define KHM1207A_H

class KHM1207
{
    public:
        KHM1207();
        void run_demo(void);
        void print(float number);

    private:
        void set_number(uint8_t value, uint8_t location);
        void set_dot(uint8_t location);
};

#endif /* KHM1207A_H */