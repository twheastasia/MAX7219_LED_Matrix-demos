//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 02_Test_Some_Effects
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

#define SPEED_TIME  100   //--> SPEED_TIME is the speed of displaying the effect.
#define PAUSE_TIME  2000  //--> PAUSE_TIME is the time delay for switching between effects.

int cnt = 0;
char my_Text[30] = "ESP32";

// Initialization of "MD_Parola" library as "Display" and its settings.
MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

//________________________________________________________________________________ VOID SETUP()
void setup() {
  // put your setup code here, to run once:

  Display.begin();
  delay(500);
  Display.setIntensity(0);  //--> Sets the intensity or brightness of the MAX7219 LED Matrix 32x8 display. Range from 0 to 15.
  Display.setInvert(false);

  Display.displayText(my_Text, PA_CENTER, SPEED_TIME, PAUSE_TIME, PA_PRINT, PA_NO_EFFECT);
  Display.displayAnimate();
  delay(2000);

  Display.displayClear();
  delay(2000);
}
//________________________________________________________________________________ 

//________________________________________________________________________________ VOID LOOP()
void loop() {
  // put your main code here, to run repeatedly:

  if (Display.displayAnimate()) {
    cnt++;
    if (cnt > 6) cnt = 1;

    if (cnt == 1) {
      Display.setTextEffect(PA_SCROLL_DOWN, PA_SCROLL_UP);
    } else if (cnt == 2) {
      Display.setTextEffect(PA_SCROLL_UP, PA_SCROLL_DOWN);
    } else if (cnt == 3) {
      strcpy(my_Text, "UTEH");
      Display.setTextAlignment(PA_CENTER);
      Display.setTextEffect(PA_OPENING, PA_CLOSING);
    } else if (cnt == 4) {
      Display.setTextEffect(PA_GROW_UP, PA_GROW_DOWN);
    } else if (cnt == 5) {
      Display.setTextEffect(PA_GROW_DOWN, PA_GROW_UP);
    } else if (cnt == 6) {
      strcpy(my_Text, "ESP32");
      Display.setTextEffect(PA_OPENING, PA_CLOSING);
    }

    // Displays the next display.
    Display.displayReset();
  }
}
//________________________________________________________________________________ 
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
