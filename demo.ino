#include "KHM1207A.h"

KHM1207 lcd;

void setup()
{
    lcd.set_number(2345);
    lcd.set_colon(true);
    lcd.set_dot(0, true);

    lcd.update();
}

void loop()
{

}