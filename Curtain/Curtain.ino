#include <ESP32Servo.h>
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>


#define R1 16
#define R2 18
#define in1 2 //L298n Motor Driver pins.
#define in2 4
#define R4 22
Servo myservo;
// prototypes
boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);
void fourthLightChanged(uint8_t brightness);

// Change this!!

// WiFi Credentials
const char* ssid = "TP-LINK_2898";
const char* password = "193599777";

// device names
String Device_1_Name = "Office light";
String Device_2_Name = "Studio light";
String Device_3_Name = "Yellow Bulb";
String Device_4_Name = "Red bulb";

boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  Serial.begin(115200);
  myservo.attach(17, 0, 90);
  myservo.write(0);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(R4, OUTPUT);

  // Initialise wifi connection
  wifiConnected = connectWifi();

  if (wifiConnected)
  {

    // Define your devices here.
    espalexa.addDevice(Device_1_Name, firstLightChanged); //simplest definition, default state off
    espalexa.addDevice(Device_2_Name, secondLightChanged);
    espalexa.addDevice(Device_3_Name, thirdLightChanged);
    espalexa.addDevice(Device_4_Name, fourthLightChanged);

    espalexa.begin();

  }

  else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }

}

void loop()
{
  espalexa.loop();
  delay(1);
}

//our callback functions
void firstLightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R1, HIGH);
      Serial.println("Device1 ON");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
    digitalWrite(R1, LOW);
    Serial.println("Device1 OFF");
  }
}

void secondLightChanged(uint8_t brightness)
{

  //Control the device
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R2, HIGH);
      Serial.println("Device2 ON");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
    digitalWrite(R2, LOW);
    Serial.println("Device2 OFF");
  }
}

void thirdLightChanged(uint8_t brightness)
{

  //Control the device
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      delay(2500);
      Serial.println("Curtain opened");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);




    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }

  else
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(2500);
    Serial.println("Curtain opened");
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}

void fourthLightChanged(uint8_t brightness)
{

  //Control the device
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R4, LOW);
      Serial.println("Device1 ON");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
    digitalWrite(R4, HIGH);
    Serial.println("Device1 ON");
  }
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
