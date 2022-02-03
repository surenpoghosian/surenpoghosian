#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4
#define PIN_RELAY 2

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

uint8_t sensor1[8] = { 0x28, 0xCD, 0x0D, 0x75, 0xD0, 0x01, 0x3C, 0xCE};

float tempSensor1;
bool b = true;
bool turned_on = false;
void setup() {
  Serial.begin(115200);
  delay(100);
  sensors.begin();
  pinMode(PIN_RELAY, OUTPUT);
  delay(1000);
  digitalWrite(PIN_RELAY, LOW);
}



void loop() {

  sensors.requestTemperatures();
  tempSensor1 = sensors.getTempC(sensor1); // Gets the values of the temperature
  Serial.println(tempSensor1);

  if (tempSensor1 > 34.0 ) {
    if (turned_on) {
      return
    }
    else {
      Serial.println("Turned on\n");
      digitalWrite(PIN_RELAY, HIGH);
      b = false;
      turned_on = true;
    }
  }
  if (tempSensor1 < 32.0 ) {
    if (b) {
      return
    }
    else {
      Serial.println("Turned off");
      digitalWrite(PIN_RELAY, LOW);
      b = true;
      turned_on = false;
    }
  }


  delay(1000);

}
