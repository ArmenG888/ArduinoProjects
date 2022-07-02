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
    ReadKeyboard(results.value);
    //Serial.println(results.value);
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
void ReadKeyboard(int result)
{
  if (result == -9691)
  {
    Serial.print("a");
  }
  else if (result == -20911)
  {
    Serial.print("b");
  }
  else if (result == 30345)
  {
    Serial.print("c");
  }
  else if (result == -17851)
  {
    Serial.print("d");
  }
  else if (result == 24735)
  {
    Serial.print("e");
  }
  else if (result == 31365)
  {
    Serial.print("f");
  }
  else if (result == -1531)
  {
    Serial.print("g");
  }
  else if (result == 5865)
  {
    Serial.print("h");
  }
  else if (result == -5611)
  {
    Serial.print("i");
  }
  else if (result == -27031)
  {
    Serial.print("j");
  }
  else if (result == 22185)
  {
    Serial.print("k");
  }
  else if (result == -10711)
  {
    Serial.print("l");
  }
  else if (result == 7905)
  {
    Serial.print("m");
  }
  else if (result == 28305)
  {
    Serial.print("n");
  }
  else if (result == 6885)
  {
    Serial.print("o");
  }
  else if (result == -26011)
  {
    Serial.print("p");
  }
  else if (result == 8415)
  {
    Serial.print("q");
  }
  else if (result == 12495)
  {
    Serial.print("r");
  }
  else if (result == 15045)
  {
    Serial.print("s");
  }
  else if (result == -20401)
  {
    Serial.print("t");
  }
  else if (result == -27541)
  {
    Serial.print("u");
  }
  else if (result == 3825)
  {
    Serial.print("v");
  }
  else if (result == -24481)
  {
    Serial.print("w");
  }
  else if (result == -18871)
  {
    Serial.print("x");
  }
  else if (result == -4081)
  {
    Serial.print("y");
  }
  else if (result == 551499465)
  {
    Serial.print("z");
  }
  else if (result == 13260)
  {
    Serial.print(" ");
  }
  else if (result == -14536)
  {
    Serial.print("\n");
  }
  else if (result == 18360)
  {
    Serial.print("<DELETE>");
  }
}
  
