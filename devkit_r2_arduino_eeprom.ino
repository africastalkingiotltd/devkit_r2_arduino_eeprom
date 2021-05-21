#include <EEPROM.h>
#include "./data.h"

#define LED_PIN PC13
// Set both these flags to 1 to set everything up, then set it to 0
#define SHOULD_CLEAR_EEPROM 0 // Set to 1 if you want the EEPROM to be cleared.
#define SHOULD_SET_UP 0 // Set to 1 if you want to setup stuff


void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
        ; // Do something else that shows the Serial (UART1) is not working;
    }
    pinMode(LED_PIN, OUTPUT);
    if (SHOULD_CLEAR_EEPROM)
    {
        Serial.println("Clearing EEPROM");
        clearEEPROM();
    }
    else
    {
        Serial.println("Not clearing EEPROM");
    }

    Flag getFlag;
    Setup setupData;

    int flagAddress = sizeof(float); // A small offset
    int setupAddress = 0;
    setupAddress += flagAddress + sizeof(Flag);

    if (SHOULD_SET_UP)
    {
        // The flag has not been set. Let set it
        int flag_ = (int)getRandom(0, 1);
        getFlag.set = flag_;
        setFlag(getFlag, flagAddress);

        // Also this maybe a good time to set the setup info as well
        char deviceID[25];
        generateRandomChars(deviceID, sizeof(deviceID));
        long magik = getRandom(10, 200);
        int mode = (int)getRandom(42, 69);
        strcpy(setupData.deviceID, deviceID);
        setupData.magicNum = magik;
        setupData.mode = mode;
        setupOp(setupData, setupAddress);
    }
    else
    {
        // We have stuff in the EEPROM
        EEPROM.get(flagAddress, getFlag);
        EEPROM.get(setupAddress, setupData);
        char output[100];
        snprintf(output, sizeof(output), "Device ID: %s, Mode: %d, Magic Number: %lu", setupData.deviceID, setupData.mode, setupData.magicNum);
        Serial.println(output);
        Serial.print("LED will be toggled: ");
        Serial.println(getFlag.set);
        digitalWrite(LED_PIN, getFlag.set);
    }
}

void loop()
{
    // Nothing doing
}
