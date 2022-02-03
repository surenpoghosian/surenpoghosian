#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 15 on the ESP32
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

uint8_t sensor1[8] = { 0x28, 0xCD, 0x0D, 0x75, 0xD0, 0x01, 0x3C, 0xCE};

float tempSensor1;

void setup() {
  Serial.begin(115200);
  delay(100);

  sensors.begin();

  }



void loop() {
  sensors.requestTemperatures();
  tempSensor1 = sensors.getTempC(sensor1); // Gets the values of the temperature
  Serial.println(tempSensor1);
  delay(1000); 

}
