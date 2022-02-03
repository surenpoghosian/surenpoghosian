//Sensor pins
#define BTN_PIN 14
#define  humidity_SENSOR  12
#define TEMPERATURE 4
#define PIN_RELAY 13

//Libraries
//temperature sensor libraries
#include <OneWire.h>
#include <DallasTemperature.h>

//real time module libraries
#include <Wire.h>
#include "RTClib.h"

//button library
#include "GyverButton.h"

//define RTC class object
RTC_DS1307 rtc;


//states, explained below->
bool humidity = true;
bool b = true;
bool tmp_turned_on = false;
bool pump_state = false;

//temperature sensor id
uint8_t sensor1[8] = { 0x28, 0xCD, 0x0D, 0x75, 0xD0, 0x01, 0x3C, 0xCE};

//week days for RTC module
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//variable for temperature value
float tempSensor1;

//declaring objects
OneWire oneWire(TEMPERATURE);
GButton butt1(BTN_PIN);
DallasTemperature sensors(&oneWire);


//void setup works once, only when the device boots,its intended for single settings setup

void setup() {
  while (!Serial);                 //Serial port intended for value monitoring

  Serial.begin(115200);           //running serial port on speed 115200 bids
  if (! rtc.begin()) {             // if there is no signal on i2c port (scl,sca/21,22) send message about it

    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");

    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    // This line sets the RTC with an explicit date & time, for example to set
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  //defining port 2 as output, it means that we will return to that port 1 or 0 (HIGH/LOW)
  pinMode(2, OUTPUT);

  //defining port PIN_RELAY(13 port) as output, it means that we will return to that port 1 or 0 (HIGH/LOW)
  pinMode(PIN_RELAY, OUTPUT);

  //waiting one second to load data
  delay(1000);

  //starting sensors
  sensors.begin();

  //setting relay state as LOW to prevent accidental activation when device booting
  digitalWrite(PIN_RELAY, LOW);


}
//function for blinking led light for  current mode monintoring
void blink(int port) {

  digitalWrite(port, HIGH);
  delay(100);
  digitalWrite(port, LOW);

}


//void loop is a loop

void loop() {
  //checking signal from button
  butt1.tick();

  //if its a single click->
  if (butt1.isSingle()) {
    Serial.println("Single");
    
    //blink once, port 2 as atribute (to this port connected integrated led light)
    blink(2);

    //while humidity is true, we can change it to false and check it inside the while loop so we can stop the loop
    while (humidity) {

      //reading humidity sensor analog signal and converting it to uint16_t format
      uint16_t sensor = analogRead(humidity_SENSOR);

      //then converting and reversing the values(if too wet the value is ~1200(we convert it to 1024), if not wet enough the value is above 3400(converted to 0<))
      uint16_t sensor_converted = map(sensor, 1200, 3600, 1024, 0);
      
      //printing humidity value in Serial monitor
      Serial.println(sensor_converted);
      
      //checking the value and turning on//off the pump
      if (sensor_converted < 200) {
      
        //if pump_state is false(pump is turned off)
        if (! pump_state) {
        
          //turn it on
          Serial.println("Turning on\n");
          digitalWrite(PIN_RELAY, HIGH);
          pump_state = true;

        }

      }
      if (sensor_converted > 600) {

        //if pump_state is true(pump is turned on)
        if (pump_state) {
        
          //turn it off
          Serial.println("Turning off");
          digitalWrite(PIN_RELAY, LOW);
          Serial.println("Turned off\n");
          pump_state = false;

        }

      }
      //wait a second
      delay(1000);
    }
  }
  //if button click is double ->
  if (butt1.isDouble()) {

    //blink twice
    for (int i = 0; i < 2; i++) {
      blink(2);
      delay(100);
    }
    
    //starting a while loop
    while (true) {
    
      //getting temperature
      sensors.requestTemperatures();
      tempSensor1 = sensors.getTempC(sensor1);
      
      //printing temperature in Serial monitor
      Serial.println(tempSensor1);
      delay(1000);

      //if temperature is above 34
      if (tempSensor1 > 34.0 ) {

        //and if tmp_turned_on is true(tmp_turned_on is flag for monitorning relay state when tmp is above 34)
        if (tmp_turned_on ) {

          //notificate that relay is turned ON
          Serial.println("Relay is turned ON");
        }
        else {
      
          //if its turned OFF, then turn it ON
          Serial.println("Turned on\n");
          digitalWrite(PIN_RELAY, HIGH);
          
          //b is a flag for relay state in temperature sensor part
          b = false;

          tmp_turned_on  = true;
        }
      }
      if (tempSensor1 < 32.0 ) {

        if (b) { //(b is flag for monitorning relay state when tmp is below 32)
       
          //do not turn OFF relay when temperature is below 32  when its already turned off
          Serial.println("Relay is turned OFF");
        }
        else {
          
          //if relay turned ON and temperature is below 32 then turn it OFF
          Serial.println("Turned off");
          digitalWrite(PIN_RELAY, LOW);

          b = true;
          tmp_turned_on  = false;
        }
      }



    }

  }
  // if button clicked 3 times
  if (butt1.isTriple()) {

    //blink 3 times
    Serial.println("Triple");
    for (int i = 0; i < 3; i++) {
      blink(2);
      delay(100);
    }
    
    //starting while loop
    while (true) {

      //creating <now> pointer
      DateTime now = rtc.now();

      //correcting time
      DateTime future (now + TimeSpan(0, 0, 0, 20));

      //printing year
      Serial.print(future.year(), DEC);
      Serial.print('/');


      //printing month
      Serial.print(future.month(), DEC);
      Serial.print('/');

      //printing day
      Serial.print(future.day(), DEC);
      Serial.print(' ');

      //printing hour
      Serial.print(future.hour(), DEC);
      Serial.print(':');

      //printing minute
      Serial.print(future.minute(), DEC);
      Serial.print(':');

      //printing second
      Serial.print(future.second(), DEC);
      Serial.println();
      Serial.println();
    
      //declaring seconds variable
      int sec = future.second();

      //blinking interval set to 10 second (example: if its divisible to 10 without reminder)
      if (sec % 10 == 0) {
        //blink once
        blink(2);
      }
      //wait a second
      delay(1000);
    }
  }
}
