#include <EEPROM.h>

typedef struct Setup
{
    char deviceID[30];
    int mode;
    long magicNum;
} Setup;

typedef struct Flag
{
    byte set;
} Flag;

long getRandom(byte min, byte max)
{
    randomSeed(analogRead(micros()));
    return random(min, max);
}

void clearEEPROM()
{
    Serial.print("Internal EEPROM Size: ");
    Serial.println(EEPROM.length());
    Serial.println("Cleaning up EEPROM");
    for (int i = 0; i < EEPROM.length(); i++)
    {
        eeprom_buffered_write_byte(i, 0);
    }
    eeprom_buffer_flush();
    Serial.println("Done Cleaning up EEPROM");
    Serial.flush();
}

void generateRandomChars(char *dest, size_t length)
{
  randomSeed(analogRead(micros()));
  char charset[] = "01abcdef2pqrstuvw5nox"
                   "g89hij34klyzKLMNOPQ6m"
                   "IJRSTUABCDEFGHVWXYZ7";

  while (length-- > 0)
  {
    size_t index = (double)rand() / RAND_MAX * ((sizeof(charset) - 1));
    *dest++ = charset[index];
  }
  *dest = '\0';
}

void setFlag(Flag _flag, int _flagAddress)
{
    Serial.println("Setting the flag...");
    Serial.flush();
    EEPROM.put(_flagAddress, _flag);
    Serial.println("Done updating Flag...");
    Serial.flush();
}

void setupOp(Setup _setup, int _setupAddress)
{
    Serial.println("Setting the Setup info...");
    Serial.flush();
    EEPROM.put(_setupAddress, _setup);
    Serial.println("Done updating Setup data...");
    Serial.flush();
}