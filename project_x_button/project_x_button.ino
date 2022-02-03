#define BTN_PIN 14
#define  SENSOR  12
#define ONE_WIRE_BUS 4
#define PIN_RELAY 13


#include <OneWire.h>
#include <DallasTemperature.h>

#include <Wire.h>
#include "RTClib.h"

#include "GyverButton.h"

RTC_DS1307 rtc;

bool humidity = true;
bool b = true;
bool tmp_turned_on = false;
bool pump_state = false;

uint8_t sensor1[8] = { 0x28, 0xCD, 0x0D, 0x75, 0xD0, 0x01, 0x3C, 0xCE};
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

float tempSensor1;


OneWire oneWire(ONE_WIRE_BUS);
GButton butt1(BTN_PIN);
DallasTemperature sensors(&oneWire);

void setup() {
  while (!Serial);
  Serial.begin(115200);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  pinMode(2, OUTPUT);
  pinMode(PIN_RELAY, OUTPUT);
  delay(1000);
  sensors.begin();
  digitalWrite(PIN_RELAY, LOW);


}

void blink(int port) {
  digitalWrite(port, HIGH);
  delay(100);
  digitalWrite(port, LOW);
}

void loop() {

  butt1.tick();
  if (butt1.isSingle()) {
    Serial.println("Single");
    blink(2);
    while (humidity) {

      uint16_t sensor = analogRead(SENSOR);
      uint16_t sensor_converted = map(sensor, 1200, 3600, 1024, 0);
      Serial.println(sensor_converted);
      if (sensor_converted < 200) {
        if (! pump_state) {
          Serial.println("Turning on\n");
          digitalWrite(PIN_RELAY, HIGH);
          pump_state = true;

        }

      }
      if (sensor_converted > 600) {
        if (pump_state) {
          Serial.println("Turning off");
          digitalWrite(PIN_RELAY, LOW);
          Serial.println("Turned off\n");
          pump_state = false;

        }

      }
      delay(1000);
    }
  }

  if (butt1.isDouble()) {
    for (int i = 0; i < 2; i++) {
      blink(2);
      delay(100);
    }
    while (true) {
      sensors.requestTemperatures();
      tempSensor1 = sensors.getTempC(sensor1);

      Serial.println(tempSensor1);
      delay(1000);
      if (tempSensor1 > 34.0 ) {
        if (tmp_turned_on ) {
          Serial.println("Relay is turned ON");
        }
        else {
          Serial.println("Turned on\n");
          digitalWrite(PIN_RELAY, HIGH);
          b = false;
          tmp_turned_on  = true;
        }
      }
      if (tempSensor1 < 32.0 ) {
        if (b) {
          Serial.println("Relay is turned OFF");
        }
        else {
          Serial.println("Turned off");
          digitalWrite(PIN_RELAY, LOW);
          b = true;
          tmp_turned_on  = false;
        }
      }



    }

  }

  if (butt1.isTriple()) {
    Serial.println("Triple");
    for (int i = 0; i < 3; i++) {
      blink(2);
      delay(100);
    }
    while (true) {
      DateTime now = rtc.now();
      DateTime future (now + TimeSpan(0, 0, 0, 20));

      Serial.print(future.year(), DEC);
      Serial.print('/');
      Serial.print(future.month(), DEC);
      Serial.print('/');
      Serial.print(future.day(), DEC);
      Serial.print(' ');
      Serial.print(future.hour(), DEC);
      Serial.print(':');
      Serial.print(future.minute(), DEC);
      Serial.print(':');
      Serial.print(future.second(), DEC);
      Serial.println();
      Serial.println();
      int sec = future.second();

      if (sec % 10 == 0) {
        digitalWrite(2, HIGH);
        delay(100);
        digitalWrite(2, LOW);
      }
      delay(1000);
    }
  }
}
