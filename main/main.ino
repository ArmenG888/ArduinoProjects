#include <IRremote.hpp>
#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);


int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
String input = "";
String key = "";
void setup()
{
  
    Serial.begin(9600);
    lcd.begin();
    lcd.backlight();
    pinMode(2, OUTPUT);  
    irrecv.enableIRIn();
    int bytes_empty = 0;
    int x = 0;
    lcd.setCursor(0,0);
    lcd.print("booting...");
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
   lcd.setCursor(0,3);
   lcd.print(1024-bytes_empty);
   lcd.print("/1024B ");
   lcd.setCursor(0,0);
   lcd.print("          ");
}
   

void loop()
{
  
  if (irrecv.decode(&results))
  {
    key = ReadKeyboard(results.value);
    if (key == "<ENTER>")
    {
      input = "";
      lcd.setCursor(0,0);
      lcd.print("                        ");
    }
    else
    {
      input += key;
    }
    lcd.setCursor(0,0);
    lcd.print(input);
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
String ReadKeyboard(int result)
{
  if (result == -9691)
  {
    return "a";
  }
  else if (result == -20911)
  {
    return "b";
  }
  else if (result == 30345)
  {
    return "c";
  }
  else if (result == -17851)
  {
    return "d";
  }
  else if (result == 24735)
  {
    return "e";
  }
  else if (result == 31365)
  {
    return "f";
  }
  else if (result == -1531)
  {
    return "g";
  }
  else if (result == 5865)
  {
    return "h";
  }
  else if (result == -5611)
  {
    return "i";
  }
  else if (result == -27031)
  {
    return "j";
  }
  else if (result == 22185)
  {
    return "k";
  }
  else if (result == -10711)
  {
    return "l";
  }
  else if (result == 7905)
  {
    return "m";
  }
  else if (result == 28305)
  {
    return "n";
  }
  else if (result == 6885)
  {
    return "o";
  }
  else if (result == -26011)
  {
    return "p";
  }
  else if (result == 8415)
  {
    return "q";
  }
  else if (result == 12495)
  {
    return "r";
  }
  else if (result == 15045)
  {
    return "s";
  }
  else if (result == -20401)
  {
    return "t";
  }
  else if (result == -27541)
  {
    return "u";
  }
  else if (result == 3825)
  {
    return "v";
  }
  else if (result == -24481)
  {
    return "w";
  }
  else if (result == -18871)
  {
    return "x";
  }
  else if (result == -4081)
  {
    return "y";
  }
  else if (result == 551499465)
  {
    return "z";
  }
  else if (result == 13260)
  {
    return " ";
  }
  else if (result == -14536)
  {
    return "<ENTER>";
  }
  else if (result == 18360)
  {
    return "<DELETE>";
  }
  return "";
}
  
