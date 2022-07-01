#include <EEPROM.h>
int x = 1000;
void setup()
{
  
    Serial.begin(9600);
    writeStringToEEPROM(800,"3fdfsd jkf dsf sdkjlf dsflkjds flkjds l");
    Serial.println(readStringFromEEPROM(700));
    pinMode(2, OUTPUT);  
    int bytes_empty = 0;
    for (int i=0; i < 1024; i++)
    { 
      if (EEPROM.read(i) != 255)
      {
        Serial.print("Byte ");
        Serial.print(i+1);
        Serial.print(" = (");
        Serial.print("Hexadecimal:");
        Serial.print(EEPROM.read(i));
        Serial.print(", Decimal:");
        Serial.print(EEPROM.read(i),HEX);
        Serial.println(")");
        
      }
      else{
        bytes_empty++;
      }
    }
    
   Serial.print(1024-bytes_empty);
   Serial.print(" bytes ");
   Serial.print("used out of 1024. ");
   Serial.print(bytes_empty);
   Serial.print(" bytes left");
   
   
}

void loop()
{
  digitalWrite(2, HIGH); 
  delay(x); 
  digitalWrite(2, LOW); 
  delay(x);
  if (x > 100)
  {
    x -= 10;
  }
  else{
    x -= 1;
  }
  if (x == 0)
  {
    x = 1000;
  }
}
void writeStringToEEPROM(int addrOffset, const String &strToWrite)
{
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
}
String readStringFromEEPROM(int addrOffset)
{
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  return String(data);
}
    
