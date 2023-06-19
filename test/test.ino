#include <EEPROM.h>

void setup()
{
  Serial.begin(9600);
  
  for (int i = 0; i < 255; i++)
  {
    EEPROM.write(i, 0);
  }
  int x = 0;
  for (int i = 0; i < 1024; i++)
  {
    int data = EEPROM.read(i);
    if(data != 255){
      Serial.println(data, DEC);
      x += 1;
    }
    Serial.print(x);
    Serial.print("/1024b");
    
  }
    
}
void loop(){}
