//Sensor pins
#define  SENSOR  12
#define PIN_RELAY 13
#define LED 2

//states for checking relay state(on/off)
bool flag = true;

void setup() {
  //Serial port intended for value monitoring
  Serial.begin(115200);

  //declaring Led and relay state(OUTPUT or INPUT)
  pinMode(LED, OUTPUT);
  pinMode(PIN_RELAY, OUTPUT);
  delay(1000);

  //setting relay state as LOW to prevent accidental activation when device booting
  digitalWrite(PIN_RELAY, LOW);

}

void loop() {

  //reading data from analog port
  uint16_t sensor = analogRead(SENSOR);

  //converting data
  uint16_t sensor_converted = map(sensor, 1200, 3600, 1024, 0);

  Serial.println(sensor_converted);
  
  //if sensor data is below 300
  if (sensor_converted < 300) {
    
    //if its turned off
    if (flag) {

      Serial.println("Turning on\n");

      //turn it on for 2 seconds
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
