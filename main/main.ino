#include <IRremote.hpp>
#include "SPI.h"
#include "TFT_22_ILI9225.h"
#include <../fonts/FreeMono9pt7b.h>
#include <../fonts/FreeSans24pt7b.h>

#if defined (ARDUINO_ARCH_STM32F1)
#define TFT_RST PA1
#define TFT_RS  PA2
#define TFT_CS  PA0 // SS
#define TFT_SDI PA7 // MOSI
#define TFT_CLK PA5 // SCK
#define TFT_LED 0 // 0 if wired to +5V directly
#elif defined(ESP8266)
#define TFT_RST 4   // D2
#define TFT_RS  5   // D1
#define TFT_CLK 14  // D5 SCK
//#define TFT_SDO 12  // D6 MISO
#define TFT_SDI 13  // D7 MOSI
#define TFT_CS  15  // D8 SS
#define TFT_LED 2   // D4     set 0 if wired to +5V directly -> D3=0 is not possible !!
#elif defined(ESP32)
#define TFT_RST 26  // IO 26
#define TFT_RS  25  // IO 25
#define TFT_CLK 14  // HSPI-SCK
//#define TFT_SDO 12  // HSPI-MISO
#define TFT_SDI 13  // HSPI-MOSI
#define TFT_CS  15  // HSPI-SS0
#define TFT_LED 0   // 0 if wired to +5V directly
SPIClass hspi(HSPI);
#else
#define TFT_RST 8
#define TFT_RS  9
#define TFT_CS  10  // SS
#define TFT_SDI 11  // MOSI
#define TFT_CLK 13  // SCK
#define TFT_LED 3   // 0 if wired to +5V directly
#endif

#define TFT_BRIGHTNESS 200 // Initial brightness of TFT backlight (optional)

TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED, TFT_BRIGHTNESS);
int16_t x=0, y=20, w, h;

#include <IRremote.h>     
int RECV_PIN = 7; 
IRrecv irrecv(RECV_PIN);     
decode_results results;    
int menu_mode = 0;
String command = "";
String result_value = "";

void vi(){
  menu_mode = 1;
  tft.clear();
  x,y = 0,0;
  command = "";
}

String Command(String comd){
    if (comd == "cls" || comd == "clear"){
      y = 0;
      tft.clear();
      return "";
    }
    else if(comd == "vi"){
      vi();
      return "";
    }
    return "Invalid Command";
}

void display_text(String text, uint16_t color=COLOR_WHITE){
  y += h; 
  x += 10;
  if (x >= 170)
  {
    y += 20;
    x = 0;
  }
  tft.drawGFXText(x,y,text, color);  
}

// Setup
void setup() {
  
#if defined(ESP32)
  hspi.begin();
  tft.begin(hspi);
#else
  tft.begin();
#endif
  tft.clear();
  tft.setOrientation(2);
  tft.setGFXFont(&FreeMono9pt7b);  
  display_text("~");
  display_text("$", COLOR_GREEN);
  x += 10;
  Serial.begin(9600);     
  irrecv.enableIRIn();  
  pinMode(2, OUTPUT); 
}

// Loop
void loop() {
    if (irrecv.decode(&results)){  
        digitalWrite(2, HIGH);   
        delay(5);              
        digitalWrite(2, LOW);              
        result_value = ReadKeyboard(results.value);
        if (menu_mode == 0){
            if (result_value == "<DELETE>"){
              y += h;
              x -= 10;
              tft.drawGFXText(x, y," ", COLOR_WHITE); 
              
            }
            else if (result_value != "" && result_value != "<ENTER>"){
              display_text(result_value);
              command += result_value;  
            }
            else if (result_value == "<ENTER>"){
                y += 15;
                x = 0;
                y += h; 
                tft.drawGFXText(x, y, Command(command), COLOR_WHITE);
                x = 170;
                display_text("~");
                display_text("$", COLOR_GREEN);
                x += 10;
                command = "";
            }   
        }    
        else if(menu_mode == 1)
        {
          if (result_value != "" && result_value != "<ENTER>"){
              display_text(result_value);   
              command += result_value;  
          }
          else if(result_value == "<ENTER>")
          {
              y += h + 20;
              x = 0;
              command += "\n";
          }
       }
       irrecv.resume(); 
    }   
}

String ReadKeyboard(int result)
{
    if(result == -9691){return "a";}
    else if(result == -20911){return "b";}
    else if(result == 30345){return "c";}
    else if(result == -17851){return "d";}
    else if(result == 24735){return "e";}
    else if(result == 31365){return "f";}
    else if(result == -1531){return "g";}
    else if(result == 5865){return "h";}
    else if(result == -5611){return "i";}
    else if(result == -27031){return "j";}
    else if(result == 22185){return "k";}
    else if(result == -10711){return "l";}
    else if(result == 7905){return "m";}
    else if(result == 28305){return "n";}
    else if(result == 6885){return "o";}
    else if(result == -26011){return "p";}
    else if(result == 8415){return "q";}
    else if(result == 12495){return "r";}
    else if(result == 15045){return "s";}
    else if(result == -20401){return "t";}
    else if(result == -27541){return "u";}
    else if(result == 3825){return "v";}
    else if(result == -24481){return "w";}
    else if(result == -18871){return "x";}
    else if(result == -4081){return "y";}
    else if(result == 551499465){return "z";}
    else if(result == 13260){return " ";}
    else if(result == -14536){return "<ENTER>";}
    else if(result == 31620){return ",";}
    else if(result == 32640){return ".";}
    else if(result == 21420){return ":";}
    else if(result == 10200){return "?";}
    else if(result == 18360){return "<DELETE>";}
    else if(result == -23971){return "1";}
    else if(result == 25245){return "2";}
    else if(result == -7651){return "3";}
    else if(result == 8925){return "4";}
    else if(result == 765){return "5";}
    else if(result == -15811){return "6";}
    else if(result == -8161){return "7";}
    else if(result ==  -22441){return "8";}
    else if(result ==  -28561){return "9";}
    else if(result ==  -26521){return "0";}
    else if(result ==  14535){return "<OK>";}
    else{return "";}
}
