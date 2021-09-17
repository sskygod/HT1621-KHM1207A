#include "HT1621Driver.h"

#define START_SEGMENT       0x00
#define END_SEGMENT         0x1F

#define BLANK               0x00

/* Send length */
#define COMMAND_ID_LEN      3u
#define COMMAND_CODE_LEN    9u
#define ADDRESS_LEN         6u
#define DATA_LEN            8u      // Send Successive for two addresses
#define ALL_DATA_LEN        128u    // 32 segment * 4 bit

HT1621::HT1621()
{
    
}

HT1621::HT1621(uint8_t cs_pin, uint8_t wr_pin, uint8_t data_pin)
{
    cs_pin_def = cs_pin;
    wr_pin_def = wr_pin;
    data_pin_def = data_pin;

    pinMode(cs_pin_def, OUTPUT);
	pinMode(wr_pin_def, OUTPUT);
	pinMode(data_pin_def, OUTPUT);

    HT1621();
}

void HT1621::send_cmd(uint16_t command_code) 
{
    digitalWrite(cs_pin_def, LOW);

    send(CMD, COMMAND_ID_LEN);
    send(command_code, COMMAND_CODE_LEN);

    digitalWrite(cs_pin_def, HIGH);
}

void HT1621::send_data(uint8_t segment, uint8_t val)
{
    digitalWrite(cs_pin_def, LOW);

    send(WRITE, COMMAND_ID_LEN);
    send(segment, ADDRESS_LEN);
    send(val, DATA_LEN);

    digitalWrite(cs_pin_def, HIGH);
}

void HT1621::clear_ram(void)
{
    digitalWrite(cs_pin_def, LOW);

    send(WRITE, COMMAND_ID_LEN);
    send(START_SEGMENT, ADDRESS_LEN);

    for (uint8_t i = START_SEGMENT; i <= END_SEGMENT; i++)
    {
        send(BLANK, DATA_LEN);
    }

    digitalWrite(cs_pin_def, HIGH);
}

void HT1621::send(uint16_t data, uint8_t len)
{
    data <<= (16u - len);

    for (uint8_t i = 0u; i < len; i++)
    {
        digitalWrite(wr_pin_def, LOW);
		delayMicroseconds(4);

		if (data & 0x8000) {
			digitalWrite(data_pin_def, HIGH);
		}
		else
		{
			digitalWrite(data_pin_def, LOW);
		}

		digitalWrite(wr_pin_def, HIGH);
		delayMicroseconds(4);

		data <<= 1;
    }
}
