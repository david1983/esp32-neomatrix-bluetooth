// Adafruit_NeoMatrix example for single NeoPixel Shield.
// By Marc MERLIN <marc_soft@merlins.org>
// Contains code (c) Adafruit, license BSD

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 15

// ESP8266 has an I2S neopixel library which can only use pin RX
// so it's recommended to use the same pin with Neopixel to avoid
// rewiring when changing libs
#ifdef ESP8266
#define PIN RX
#endif

//#define P32BY8X4
#define P16BY16X4
#if defined(P32BY8X4) || defined(P16BY16X4)
#define BM32
#endif


#define mw 8
#define mh 8
Adafruit_NeoMatrix *matrix = new Adafruit_NeoMatrix(mw, mh, 
  PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
    NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800 );

// This could also be defined as matrix->color(255,0,0) but those defines
// are meant to work for adafruit_gfx backends that are lacking color()
#define LED_BLACK    0

#define LED_RED_VERYLOW   (3 <<  11)
#define LED_RED_LOW     (7 <<  11)
#define LED_RED_MEDIUM    (15 << 11)
#define LED_RED_HIGH    (31 << 11)

#define LED_GREEN_VERYLOW (1 <<  5)   
#define LED_GREEN_LOW     (15 << 5)  
#define LED_GREEN_MEDIUM  (31 << 5)  
#define LED_GREEN_HIGH    (63 << 5)  

#define LED_BLUE_VERYLOW  3
#define LED_BLUE_LOW    7
#define LED_BLUE_MEDIUM   15
#define LED_BLUE_HIGH     31

#define LED_ORANGE_VERYLOW  (LED_RED_VERYLOW + LED_GREEN_VERYLOW)
#define LED_ORANGE_LOW    (LED_RED_LOW     + LED_GREEN_LOW)
#define LED_ORANGE_MEDIUM (LED_RED_MEDIUM  + LED_GREEN_MEDIUM)
#define LED_ORANGE_HIGH   (LED_RED_HIGH    + LED_GREEN_HIGH)

#define LED_PURPLE_VERYLOW  (LED_RED_VERYLOW + LED_BLUE_VERYLOW)
#define LED_PURPLE_LOW    (LED_RED_LOW     + LED_BLUE_LOW)
#define LED_PURPLE_MEDIUM (LED_RED_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_PURPLE_HIGH   (LED_RED_HIGH    + LED_BLUE_HIGH)

#define LED_CYAN_VERYLOW  (LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_CYAN_LOW    (LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_CYAN_MEDIUM   (LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_CYAN_HIGH   (LED_GREEN_HIGH    + LED_BLUE_HIGH)

#define LED_WHITE_VERYLOW (LED_RED_VERYLOW + LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_WHITE_LOW   (LED_RED_LOW     + LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_WHITE_MEDIUM  (LED_RED_MEDIUM  + LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_WHITE_HIGH    (LED_RED_HIGH    + LED_GREEN_HIGH    + LED_BLUE_HIGH)

int brightness=255;

BluetoothSerial SerialBT;

const char* ssid     = "ArduinoLed-ESP";
const char* password = "1234567890";

void setup() {
    SerialBT.begin(ssid); //Bluetooth device name
    Serial.begin(115200);
    matrix->begin();
    matrix->setTextWrap(false);
    matrix->setBrightness(brightness);
    // Test full bright of all LEDs. If brightness is too high
    // for your current limit (i.e. USB), decrease it.
    matrix->fillScreen(LED_WHITE_HIGH);
    matrix->clear();
}

void fillScreen(int color, int delay_ms){
    matrix->setBrightness(brightness);
    matrix->fillScreen(color);
    matrix->show();
    delay(delay_ms);
    matrix->clear();
}
int r = 0;
int g = 0;
int b = 0;

String key;
int value;
void loop() {
  while(Serial.available()>0){
    key=Serial.readStringUntil('=');
    value=Serial.readStringUntil('\n').toInt();
  }
  while(SerialBT.available()>0){
    key=SerialBT.readStringUntil('=');
    value=SerialBT.readStringUntil('\n').toInt();
  }


  if(key=="r"){r=value;}
  if(key=="g"){g=value;}
  if(key=="b"){b=value;}
  if(key=="bright"){brightness=value;}
  
  fillScreen(matrix->Color(r,g,b), 10);    
}
