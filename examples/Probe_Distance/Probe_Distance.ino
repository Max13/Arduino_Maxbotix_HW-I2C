/*
|--------------------------------------------------------------------------
| Maxbotix Hardware I2C Example
| - Probe distance in cm every second
|--------------------------------------------------------------------------
|
| Author: Adnan RIHAN
| URL: https://github.com/Max13/Maxbotix_I2C
| Licence: CC BY 3.0 (https://creativecommons.org/licenses/by/3.0/)
|
*/

#include    <Maxbotix_I2C.h>

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
    byte    error = 0;

    Serial.print("Probing sonar: ");
    range = sonar.probe();

    // If range < 0, it means there is an error with the I2C communication
    // If range == 0 (or max), it means there is an error with the probe
    if (range < 0) {
        Serial.print("Error(");
        Serial.print(range);
        Serial.println(")");
    } else {
        Serial.print(range);
        Serial.println("cm");
    }

    delay(1000);
}
