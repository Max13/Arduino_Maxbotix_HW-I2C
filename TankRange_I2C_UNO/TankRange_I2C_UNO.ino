/*
|--------------------------------------------------------------------------
| Maxbotix Hardware I2C
|--------------------------------------------------------------------------
|
| Author: Adnan RIHAN
| URL: https://github.com/Max13/Maxbotix
| Licence: CC BY 3.0 (https://creativecommons.org/licenses/by/3.0/)
|
*/

#include <Wire.h>

// Uncomment this line to show debug
#define SERIAL_DEBUG

// These are the default I2C pins on Arduino UNO
#define SDA_PIN     A4
#define SCL_PIN     A5

#define I2C_TIMEOUT     100
#define RETRY_TIMEOUT   10000

// The default I2C address for Maxbotix sonars
// is 224 on 8 bits, 112 on 7bits.
// Arduino I2C library currently uses 7bit addresses
#define MB_ADDR     112
#define MB_READ_CMD byte(81)

void    setup()
{
    serialInit(57600);

    pinMode(SDA_PIN, INPUT_PULLUP);
    pinMode(SCL_PIN, INPUT_PULLUP);

// Force the useless LED to stay off
#ifdef LED_BUILTIN
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
#endif

    serialPrint("* Joining I2C bus as master... ");
    Wire.begin();
    serialPrintln("Done.\n");
}

void    loop()
{
    int    range;

    do {
        range = ping(MB_ADDR);

        if (range < 0) {
            serialPrintln("* Looping in 10 seconds.");
            delay(RETRY_TIMEOUT);
        }
    } while (1);
}

void    serialInit(unsigned long baud)
{
#ifdef SERIAL_DEBUG
    Serial.begin(baud);
    while (!Serial);
    Serial.println("*Serial ready.\n");
#endif
}

byte    scanAddresses(void)
{
    byte    addr = 0;
    byte    error = 0;

    serialPrintln("* Scanning valid addresses:");

    for (byte cur = 8; cur <= 127; cur += 2) {
        serialPrint("- ");
        serialPrint(cur);
        serialPrint(": ");

        Wire.beginTransmission(cur);
        Wire.write(MB_READ_CMD);
        error = Wire.endTransmission();

        if (error != 0) {
            serialPrint("Error(");
            serialPrint(error);
            serialPrintln(")");

            continue;
        }
        serialPrintln(" OK");

        addr |= cur;
    }

    serialPrintln("* End of Scan\n");

    if (!addr) {
        serialPrintln("** No valid address found. Retrying in 10 seconds.");
    }

    return addr;
}

int    ping(byte addr)
{
    byte    error = 0;
    int     range = 0;

    serialPrint("Sending byte '");
    serialPrint(MB_READ_CMD);
    serialPrint("' to #");
    serialPrint(addr);
    serialPrint("': ");

    // Sends command byte and capture error
    Wire.beginTransmission(addr);
    Wire.write(MB_READ_CMD);
    error = Wire.endTransmission();

    // In case of an error, hangs for RETRY_TIMEOUT seconds
    if (error != 0) {
        serialPrint("Error(");
        serialPrint(error);
        serialPrintln(')');

        // To differenciate a range from an error
        // ping() will return negative error
        return -error;
    }

    serialPrintln("OK.");
    delay(I2C_TIMEOUT);

    serialPrint("Requesting 2 bytes from '");
    serialPrint(addr);
    serialPrint(": ");
    serialPrint(Wire.requestFrom(int(addr), 2));
    serialPrint(". ");

    while (byte av = Wire.available()) {
        range = Wire.read() << ((av - 1) * 8);
    }
    serialPrint(byte(range));
    serialPrintln(" cm.\n");

    return range;
}

// Serial reimplement

size_t  serialPrint(const __FlashStringHelper *data)
{
#ifdef SERIAL_DEBUG
    Serial.print(data);
#endif
}

size_t  serialPrint(const String &data)
{
#ifdef SERIAL_DEBUG
    Serial.print(data);
#endif
}

size_t  serialPrint(const char data[])
{
#ifdef SERIAL_DEBUG
    Serial.print(data);
#endif
}

size_t  serialPrint(char data)
{
#ifdef SERIAL_DEBUG
    Serial.print(data);
#endif
}

size_t  serialPrint(unsigned char data, int format = DEC)
{
#ifdef SERIAL_DEBUG
    Serial.print(data, format);
#endif
}

size_t  serialPrint(int data, int format = DEC)
{
#ifdef SERIAL_DEBUG
    Serial.print(data, format);
#endif
}

size_t  serialPrint(unsigned int data, int format = DEC)
{
#ifdef SERIAL_DEBUG
    Serial.print(data, format);
#endif
}

size_t  serialPrint(long data, int format = DEC)
{
#ifdef SERIAL_DEBUG
    Serial.print(data, format);
#endif
}

size_t  serialPrint(unsigned long data, int format = DEC)
{
#ifdef SERIAL_DEBUG
    Serial.print(data, format);
#endif
}

size_t  serialPrint(double data, int format = BIN)
{
#ifdef SERIAL_DEBUG
    Serial.print(data, format);
#endif
}

size_t  serialPrint(const Printable &data)
{
#ifdef SERIAL_DEBUG
    Serial.print(data);
#endif
}

size_t  serialPrint(const byte data)
{
#ifdef SERIAL_DEBUG
    Serial.print(data);
#endif
}

size_t  serialPrintln(const __FlashStringHelper *data)
{
#ifdef SERIAL_DEBUG
    Serial.println(data);
#endif
}

size_t  serialPrintln(const String &data)
{
#ifdef SERIAL_DEBUG
    Serial.println(data);
#endif
}

size_t  serialPrintln(const char data[])
{
#ifdef SERIAL_DEBUG
    Serial.println(data);
#endif
}

size_t  serialPrintln(char data)
{
#ifdef SERIAL_DEBUG
    Serial.println(data);
#endif
}

size_t  serialPrintln(unsigned char data, int format = DEC)
{
#ifdef SERIAL_DEBUG
    Serial.println(data, format);
#endif
}

size_t  serialPrintln(int data, int format = DEC)
{
#ifdef SERIAL_DEBUG
    Serial.println(data, format);
#endif
}

size_t  serialPrintln(unsigned int data, int format = DEC)
{
#ifdef SERIAL_DEBUG
    Serial.println(data, format);
#endif
}

size_t  serialPrintln(long data, int format = DEC)
{
#ifdef SERIAL_DEBUG
    Serial.println(data, format);
#endif
}

size_t  serialPrintln(unsigned long data, int format = DEC)
{
#ifdef SERIAL_DEBUG
    Serial.println(data, format);
#endif
}

size_t  serialPrintln(double data, int format = BIN)
{
#ifdef SERIAL_DEBUG
    Serial.println(data, format);
#endif
}

size_t  serialPrintln(const Printable &data)
{
#ifdef SERIAL_DEBUG
    Serial.println(data);
#endif
}

size_t  serialPrintln(void)
{
#ifdef SERIAL_DEBUG
    Serial.println();
#endif
}

size_t  serialPrintln(const byte data)
{
#ifdef SERIAL_DEBUG
    Serial.println(data);
#endif
}
