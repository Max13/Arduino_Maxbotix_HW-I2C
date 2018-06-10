/*
|--------------------------------------------------------------------------
| Maxbotix Hardware I2C Example
|--------------------------------------------------------------------------
|
| Author: Adnan RIHAN
| URL: https://github.com/Max13/Maxbotix
| Licence: CC BY 3.0 (https://creativecommons.org/licenses/by/3.0/)
|
*/

#include    "Maxbotix.h"

int         range;
Maxbotix    sonar;

void    setup()
{
// Force the useless LED to stay off with some clones
#ifdef LED_BUILTIN
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
#endif

    Serial.begin(57600);
    while (!Serial);
    Serial.println("Serial ready.\n");
}

void    loop()
{
    Serial.print("Probing: ");
    range = sonar.probe();

    // Range < 0 means there is an I2C error
    if (range < 0) {
        Serial.print("error(");
        Serial.print(range, DEC);
        Serial.println(")");
    } else {
        Serial.print(range, DEC);
        Serial.println("cm");
    }

    delay(2000);
}

void    scanAddresses(void)
{
    byte    error = 0;

    Serial.println("* Scanning valid addresses:");

    // Will scan all valid I2C addresses
    // See: http://www.arduino.cc/en/Reference/Wire.html
    for (byte addr = 8; addr <= 127; addr += 2) {
        Serial.print("- ");
        Serial.print(addr);
        Serial.print(": ");

        Wire.beginTransmission(addr);
        Wire.write(byte(81));
        error = Wire.endTransmission();

        if (error != 0) {
            Serial.print("Error(");
            Serial.print(error);
            Serial.println(")");

            continue;
        }
        Serial.println(" OK");
    }

    Serial.println("* End of Scan\n");
}
