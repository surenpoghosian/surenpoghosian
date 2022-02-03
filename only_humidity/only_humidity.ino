//Sensor pins
#define BTN_PIN 14
#define  SENSOR  12
#define PIN_RELAY 13
#define LED 2

//button library
#include <GyverButton.h>

//states for checking relay state(on/off)
bool flag = true;

//declaring butt1 object for button calls
GButton butt1(BTN_PIN);


//void setup works once, only when the device boots,its intended for single settings setup
void setup() {
  //Serial port intended for value monitoring
  Serial.begin(115200);
  //declaring Led and relay state(OUTPUT or INPUT)
  pinMode(LED, OUTPUT);
  pinMode(PIN_RELAY, OUTPUT);

  //wait a second
  delay(1000);

  //setting relay state as LOW to prevent accidental activation when device booting
  digitalWrite(PIN_RELAY, LOW);

}

//function for blinking led light for  current mode monintoring
void blink(int port) {
  digitalWrite(port, HIGH);
  delay(100);
  digitalWrite(port, LOW);
}

//function for relay calls, sec is working time example: work(2000);
void work(int sec) {
  digitalWrite(PIN_RELAY, HIGH);
  delay(sec);
  digitalWrite(PIN_RELAY, LOW);

}

void loop() {
  //checking signal from button

  butt1.tick();
  //if its a single click->

  if (butt1.isSingle()) {
    //blink once, port 2 as atribute (to this port connected integrated led light)

    blink(2);
    //starting loop
    while (true) {
      //reading data from analog port
      uint16_t sensor = analogRead(SENSOR);
      //converting data
      uint16_t sensor_converted = map(sensor, 1200, 3600, 1024, 0);

      Serial.println(sensor_converted);
      //if sensor data is below 300
      if (sensor_converted < 300) {
        //if its turned off
        if (flag) {
          //turn it on for 2 seconds
          Serial.println("Turning on\n");

          digitalWrite(PIN_RELAY, HIGH);
          digitalWrite(LED, HIGH);

          delay(2000);

          digitalWrite(PIN_RELAY, LOW);
          digitalWrite(LED, LOW);
          //set flag to false for delay, if it was true, the relay would turn on everytime when sensor data is below 300 without any timeout, instead of 1 time working
          flag = false;
        }
        //if sensor data is below 300 and relay already worked
        if (! flag) {
          //wait a minute
          delay(60000);
          //change flag to true, cause we already waited for timeout
          flag = true;
        }
      }
    }
  }

  //if button click is double ->
  if (butt1.isDouble()) {
    //blink twice
    for (int i = 0; i < 2; i++) {
      blink(2);
      delay(100);
    }
    //turn on relay for 2 seconds
    work(2000);
  }
}
