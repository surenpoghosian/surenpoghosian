#define BTN_PIN 14
#define  SENSOR  12
#define PIN_RELAY 13
#define LED 2

#include <GyverButton.h>


bool flag = true;
GButton butt1(BTN_PIN);

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(PIN_RELAY, OUTPUT);
  delay(1000);
  digitalWrite(PIN_RELAY, LOW);

}

void blink(int port) {
  digitalWrite(port, HIGH);
  delay(100);
  digitalWrite(port, LOW);
}

void work(int sec) {
  digitalWrite(PIN_RELAY, HIGH);
  delay(sec);
  digitalWrite(PIN_RELAY, LOW);

}

void loop() {
  butt1.tick();
  if (butt1.isSingle()) {
    blink(2);
    while (true) {
      uint16_t sensor = analogRead(SENSOR);

      uint16_t sensor_converted = map(sensor, 1200, 3600, 1024, 0);

      Serial.println(sensor_converted);

      if (sensor_converted < 300) {
        if (flag) {

          Serial.println("Turning on\n");

          digitalWrite(PIN_RELAY, HIGH);
          digitalWrite(LED, HIGH);

          delay(2000);

          digitalWrite(PIN_RELAY, LOW);
          digitalWrite(LED, LOW);
          flag = false;
        }

        if (! flag) {
          delay(60000);
          flag = true;
        }
      }
    }
  }
  if (butt1.isDouble()) {
    for (int i = 0; i < 2; i++) {
      blink(2);
      delay(100);
    }
    work(2000);
  }
}
