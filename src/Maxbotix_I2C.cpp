/*
|--------------------------------------------------------------------------
| Maxbotix Hardware I2C Library
|--------------------------------------------------------------------------
|
| Author: Adnan RIHAN
| URL: https://github.com/Max13/Maxbotix_I2C
| Licence: CC BY 3.0 (https://creativecommons.org/licenses/by/3.0/)
|
*/

#include "Maxbotix_I2C.h"

TwoWire &Maxbotix::m_i2c = Wire;

Maxbotix::Maxbotix(const byte &i2cAddress)
    : m_address(i2cAddress)
{
    pinMode(SDA, INPUT_PULLUP);
    pinMode(SCL, INPUT_PULLUP);

    m_i2c.begin();
}

int             Maxbotix::probe(const byte &sonarCmd)
{
    byte            error = 0;
    unsigned int    range = 0;

    // Sends command byte and capture error
    m_i2c.beginTransmission(m_address);
    m_i2c.write(sonarCmd);
    error = m_i2c.endTransmission();

    // To differenciate a range from an error
    // probe() will return negative error
    if (error != 0) {
        return -error;

    }

    // Wait for the impulse to come back
    delay(SONAR_WAIT);

    if (m_i2c.requestFrom(int(m_address), 2) == 2) {
        range = m_i2c.read() * 256;
        range += m_i2c.read();
    }

    m_lastProbe = range;

    return range;
}

const byte      &Maxbotix::address() const
{
    return m_address;
}

TwoWire         &Maxbotix::i2c()
{
    return m_i2c;
}

unsigned int    Maxbotix::lastProbe() const
{
    return m_lastProbe;
}

const byte      &Maxbotix::findFirstValidAddress()
{
    for (byte cur = 8; cur <= 127; cur += 2) {
        Maxbotix::m_i2c.beginTransmission(cur);
        if (Maxbotix::m_i2c.endTransmission() == 0) {
            return cur;
        }
    }

    return 0;
}
