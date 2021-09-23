#include <stdint.h>

#ifndef KHM1207A_H
#define KHM1207A_H

#define BUFFER_LEN      4u

/**
 * @brief class for driver for only LCD KHM1207 based on HT1621 chip
 * 
 */
class KHM1207
{
    public:
        /**
         * @brief Construct a new KHM1207 object
         * 
         */
        KHM1207();

        /**
         * @brief Set the number (4-digits) without dot or colon
         * 
         * @param value 
         * @return true when input value is valid (<9999)
         * @return false when input value is invalid
         */
        bool set_number(uint16_t value);

        /**
         * @brief Set the individual digit
         * 
         * @param location from 0 to 3
         * @param value from 0000 to 9999
         * @return true when input value and location is valid
         * @return false when input value or location is invalid
         */
        bool set_digit(uint8_t location, uint8_t value);

        /**
         * @brief Set the dot
         * 
         * @param location from 0 to 3
         * @param state is true or false. True is display dot, false is not display dot
         * @return true when input lcation is valid
         * @return false when input lcation is invalid
         */
        bool set_dot(uint8_t location, bool state);

        /**
         * @brief Set the colon object
         * 
         * @param state is true or false. True is display colon, false is not display colon
         */
        void set_colon(bool state);

    private:
        /**
         * @brief Store 4-digits of number before really writting them to LCD
         * 
         */
        uint8_t buffer[BUFFER_LEN];
};

#endif /* KHM1207A_H */