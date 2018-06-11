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

#ifndef MAXBOTIX_I2C_H
#define MAXBOTIX_I2C_H

#include    <Arduino.h>
#include    <Wire.h>

// Delay to wait for the sonar impulse to come back.
// Minimum recommanded is 100ms
#ifndef     SONAR_WAIT
# define    SONAR_WAIT  100
#endif

// The default I2C address for Maxbotix sonars
// is 224 on 8 bits, 112 on 7bits.
// Arduino I2C library currently uses 7bit addresses
// See: https://www.maxbotix.com/documents/I2CXL-MaxSonar-WR_Datasheet.pdf
# define    MB_ADDR     byte(112)
# define    MB_PING_CMD byte(81)

class Maxbotix
{
    private:
        const byte      &m_address;
        const byte      &m_sonarCmd;
        static TwoWire  &m_i2c;
        unsigned int    m_lastProbe;

    public:
        Maxbotix(const byte &i2cAddress = MB_ADDR, const byte &sonarCmd = MB_PING_CMD, bool pullup = true);

        int                 probe();

        const byte          &address() const;
        const byte          &sonarCmd() const;
        TwoWire             &i2c();
        unsigned int        lastProbe() const;

        static const byte   &findFirstValidAddress();
};

#endif  // MAXBOTIX_I2C_H
