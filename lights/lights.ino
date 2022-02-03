#include <Adafruit_NeoPixel.h> // подключаем библиотеку
#include "GyverButton.h"
#define PIN 8
#define POT 6
//#define POT2 7
#define POT3 5
#define POT4 0
GButton butt1(PIN);
#define PIN  9         // указываем пин для подключения ленты
#define NUMPIXELS 20  // указываем количество светодиодов в ленте
bool value = false;
int val;
//int val2;
int val3;
int val4;
// создаем объект strip с нужными характеристиками
Adafruit_NeoPixel strip (NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



void setup() {

  strip.begin();
  Serial.begin(9600);
  butt1.setTimeout(400);
  pinMode(POT, INPUT);
//  pinMode(POT2, INPUT);
  pinMode(POT3, INPUT);
  pinMode(POT4, INPUT);

}

void loop() {




  //if (butt1.isSingle()   ) {
  // поочередно включаем красный цвет




  for (int i = -1; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(val, 0, val3));
    strip.show();
    //147, 7, 192
  }





  //}
  val = analogRead(POT);
  //val2 = analogRead(POT2);
  val3 = analogRead(POT3);
  val4 = analogRead(POT4);
  val = map(val, 0, 1023, 0, 255);
  //val2 = map(val2, 0, 1023, 0, 255);
  val3 = map(val3, 0, 1023, 0, 255);
  val4 = map(val4, 0, 1023, 0, 255);
  Serial.println(val3);
  strip.setBrightness(val4);

  if ( butt1.isDouble() ) {
    for (int i = -1; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, strip.Color(147, 7, 192));
      strip.show();
      delay(20);
      Serial.println("single again");
      //147, 7, 192
      //6, 67, 249
    }
  }

  butt1.tick();

  if (butt1.isTriple()) {
    for (int i = -1; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
      strip.show();
      delay(20);


    }

  }

}
