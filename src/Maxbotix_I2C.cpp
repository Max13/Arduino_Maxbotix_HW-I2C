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

#include <Maxbotix_I2C.h>

static TwoWire  &Maxbotix::m_i2c = Wire;

Maxbotix::Maxbotix(const byte &i2cAddress, const byte &sonarCmd, bool pullup)
    : m_address(i2cAddress), m_sonarCmd(sonarCmd)
{
    if (pullup) {
        pinMode(SDA, INPUT_PULLUP);
        pinMode(SCL, INPUT_PULLUP);
    }

    m_i2c = Wire;
    m_i2c.begin();
}

int             Maxbotix::probe()
{
    byte            error = 0;
    unsigned int    range = 0;

    // Sends command byte and capture error
    m_i2c.beginTransmission(m_address);
    m_i2c.write(m_sonarCmd);
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

unsigned int    Maxbotix::lastProbe() const
{
    return m_lastProbe;
}

const byte      &Maxbotix::findFirstValidAddress(const byte &sonarCmd)
{
    for (byte cur = 8; cur <= 127; cur += 2) {
        Maxbotix::m_i2c.beginTransmission(cur);
        Maxbotix::m_i2c.write(sonarCmd);

        if (Maxbotix::m_i2c.endTransmission() == 0) {
            return cur;
        }
    }

    return 0;
}
