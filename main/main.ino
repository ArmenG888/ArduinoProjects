#include <IRremote.hpp>
#include <EEPROM.h>
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  
    Serial.begin(9600);
    pinMode(2, OUTPUT);  
    irrecv.enableIRIn();
    int bytes_empty = 0;
    int x = 0;
    for (int i=0; i < 1024; i++)
    { 
      if (EEPROM.read(i) == 255)
      {
        bytes_empty++;
        
      }
      char data;
      if (x == 10)
      {
        x = 0;
        Serial.print(" Byte:");
        Serial.print(i+1);
        Serial.print("=");
        data = EEPROM.read(i);
        Serial.println(data);
      }
      else{
        x++;
        Serial.print(" Byte:");
        Serial.print(i+1);
        Serial.print("=");
        data = EEPROM.read(i);
        Serial.print(data);
      }
      
    }
   Serial.print("\n");
   Serial.print(1024-bytes_empty);
   Serial.print(" bytes ");
   Serial.print("used out of 1024. ");
   Serial.print(bytes_empty);
   Serial.print(" bytes left");
   
   
}

void loop()
{
  if (irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    digitalWrite(2, HIGH); 
    delay(100); 
    digitalWrite(2, LOW); 
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
void Erase()
{
  for (int i = 0; i < 1024; i++)
  {
    EEPROM.write(i, 255);
}
}
