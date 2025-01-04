//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 01_Test_MAX7219_LED_Matrix_32x8
//---------------------------------------- Including Libraries.
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
//---------------------------------------- 

// Uncomment according to your hardware type.
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins.
#define MAX_DEVICES 4  //--> MAX7219 LED Matrix 32x8 consists of 4 MAX7219 LED Matrix 8x8. So "#define MAX_DEVICES 4".
#define CS_PIN 5

// Initialization of "MD_Parola" library as "Display" and its settings.
MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// 中文字符点阵数据
const uint8_t CHINESE_CHAR[] PROGMEM = {
  // 你
  0x00, 0x7C, 0x44, 0x7C, 0x40, 0x7C, 0x40, 0x00,
  0x00, 0x7C, 0x44, 0x7C, 0x40, 0x7C, 0x40, 0x00,
  // 好
  0x00, 0x7C, 0x44, 0x7C, 0x40, 0x7C, 0x40, 0x00,
  0x00, 0x7C, 0x44, 0x7C, 0x40, 0x7C, 0x40, 0x00,
};

//________________________________________________________________________________ VOID SETUP()
void setup() {
  // put your setup code here, to run once:

  Display.begin();
  delay(500);
  Display.setIntensity(10);  //--> Sets the intensity or brightness of the MAX7219 LED Matrix 32x8 display. Range from 0 to 15.
  Display.setInvert(false);
}
//________________________________________________________________________________ 

//________________________________________________________________________________ VOID LOOP()
void loop() {
  // put your main code here, to run repeatedly:

  int hours = 0; // 设置初始小时
  int minutes = 30; // 设置初始分钟
  int seconds = 0; // 设置初始秒

  while (minutes > 0 || seconds > 0) {
    Display.displayClear();
    Display.setTextAlignment(PA_CENTER);

    // 格式化时间字符串
    char timeStr[9];
    sprintf(timeStr, "%02d:%02d", minutes, seconds);
    Display.print(timeStr);

    delay(1000); // 延迟1秒

    // 更新倒计时时间
    if (seconds > 0) {
      seconds--;
    } else {
      seconds = 59;
      if (minutes > 0) {
        minutes--;
      } else {
        minutes = 59;
        if (hours > 0) {
          hours--;
        }
      }
    }
  }

  // 倒计时结束后显示 "END"
  Display.displayClear();
  Display.setTextAlignment(PA_CENTER);
  Display.print("END");
  delay(5000); // 显示5秒
}
//________________________________________________________________________________ 
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

