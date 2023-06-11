#include <IRremote.hpp>
#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);


int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup()
{
  
    Serial.begin(9600);
    lcd.begin();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("booting...");
    Erase();
    pinMode(2, OUTPUT);  
    irrecv.enableIRIn();
    int bytes_empty = 0;
    int x = 0;
    
    for (int i=0; i < 512; i++)
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
   Serial.print(512-bytes_empty);
   Serial.print(" bytes ");
   Serial.print("used out of 512. ");
   Serial.print(bytes_empty);
   Serial.print(" bytes left");
  lcd.setCursor(0,0);
  lcd.print(512-bytes_empty);
  lcd.print("/512B    ");
  lcd.setCursor(2,1);
  lcd.print("Create Files");
  lcd.setCursor(2,2);
  lcd.print("Files");
  lcd.setCursor(2,3);
  lcd.print("Apps");
  
}
   

void loop()
{
  int selected_option = mainMenu();
  Serial.println(selected_option);
  if (selected_option == 1)
  {
    create_file();
    
  }
  else if (selected_option == 2)
  {
    files();
  }
  else if (selected_option == 3)
  {
    apps();
  }
  // ok 14535
  // up 6375
  // left 4335
  // right 23205
  // down 19125
}

void create_file()
{
  clean_screen();
  lcd.setCursor(0,0);
  lcd.print("File Name:"); 
  String fileName = keyboard_input(10,0,"<ENTER>");
  clean_screen();
  lcd.setCursor(0,0);
  lcd.print("<");
  lcd.print(fileName);
  lcd.print(">");
  String fileData = keyboard_input(0,1,"<OK>");
  int len = fileName.length() + fileData.length();
  len += String(fileName.length()).length();
  len += String(fileData.length()).length();
  int addr;
  for (int i=0; i < 512; i++)
  {
    int x = 0;
    if ( EEPROM.read(i) == 255 )
    {
      for (int ii=i; ii < 512; ii++)
      {
        if (EEPROM.read(i) == 255)
        {
          x++;
        }
      }
      if (x > len)
      {
        addr = i;
        break;
      }
    }
  }
  Serial.print("Addr:");
  Serial.println(addr);
  String input = String(fileName.length()) + fileName + String(fileData.length()) + fileData;
  writeStringToEEPROM(addr,input);
  Serial.println(input);
  clean_screen();
  
}
void files()
{
  
}
void apps()
{
  
}
String keyboard_input(int x, int y, String button)
{
  String input;
  String key;
  while (true)
  {
    if (irrecv.decode(&results))
    {
      Serial.println(input[input.length()]);
      key = ReadKeyboard(results.value);
      if (key == "<DELETE>")
      {
        input = "";
        lcd.setCursor(x,y);
        lcd.print("                                                         ");
      }
      else if (key == button)
      {
        break;
      }
      else if(key == "<OK>" or key == "<ENTER>")
      {
        irrecv.resume();
      }
      else
      {
        input += key;
      }
      lcd.setCursor(x,y);
      lcd.print(input);
      digitalWrite(2, HIGH); 
      delay(100); 
      digitalWrite(2, LOW); 
      irrecv.resume();
      
    } 
    
  }
  return input;
}
void clean_screen()
{
  for (int i=0; i<4; i++)
  {
    lcd.setCursor(0,i);
    lcd.print("                              ");
  }
}

int mainMenu()
{
  int menu_page_int = 1;
  while (true)
  {
    lcd.setCursor(0,menu_page_int);
    lcd.print("<>");
    if (irrecv.decode(&results))
    {
      Serial.println(results.value);
      if (results.value == 16718055)
      {
        menu_page_int--;
        if (menu_page_int < 1)
        {
          menu_page_int=3;
        }
      }
      else if(results.value == 16730805)
      {
        menu_page_int++;
        if (menu_page_int > 3)
        {
          menu_page_int=1;
        }
      }
      else if(results.value == 16726215)
      {
        break;
      }
      for (int i = 1; i < 4; i++)
      {
        lcd.setCursor(0,i);
        lcd.print("  ");
      }
      lcd.setCursor(0,menu_page_int);
      lcd.print("<>");
      digitalWrite(2, HIGH); 
      delay(100); 
      digitalWrite(2, LOW);
      irrecv.resume(); 
    }
  }
  
  return menu_page_int;
}

void writeStringToEEPROM(int addrOffset, const String &strToWrite)
{
  Serial.println(strToWrite);
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
  for (int i = 0; i < 512; i++)
  {
    EEPROM.write(i, 255);
  }
}
String ReadKeyboard(int result)
{
  Serial.println(result);
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
  else if (result == 31620)
  {
    return ",";
  }
  else if (result == 32640)
  {
    return ".";
  }
  else if (result == 21420)
  {
    return ":";
  }
  else if (result == 10200)
  {
    return "?";
  }
  else if (result == 18360)
  {
    return "<DELETE>";
  }
  else if(result == -23971)
  {
    return "1";
  }
  else if(result == 25245)
  {
    return "2";
  }
  else if(result == -7651)
  {
    return "3";
  }
  else if(result == 3021)
  {
    return "4";
  }
  else if(result == 765)
  {
    return "5";
  }
  else if(result == -15811)
  {
    return "6";
  }
  else if(result == -8161)
  {
    return "7";
  }
  else if(result ==  -22441)
  {
    return "8";
  }
  else if(result ==  -28561)
  {
    return "9";
  }
  else if(result ==  -26521)
  {
    return "0";
  }
  else if(result ==  14535)
  {
    return "<OK>";
  }
  return "";
}
  
