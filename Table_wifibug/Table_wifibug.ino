#include <Adafruit_NeoPixel.h>
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266wifi.h>
#endif
#include <Espalexa.h>



#define PIN  10
#define NUMPIXELS 100
#define R1 16
#define R2 2
#define R3 4
#define R4 15
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
String Device_1_Name = "Light 2";
String Device_2_Name = "Table light";
String Device_3_Name = "Plug";
String Device_4_Name = "Lights";

boolean wifiConnected = false;

Espalexa espalexa;
Adafruit_NeoPixel strip (NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup()
{
  Serial.begin(115200);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  strip.begin();
  strip.setBrightness(240);
}

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
      for (int i = -1; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, strip.Color(255,0,0));
      strip.show();
      delay(20);
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
     for (int i = +1; i < NUMPIXELS; i--) {
      strip.setPixelColor(i, strip.Color(0,0,0));
      strip.show();
      delay(20);
  }
}
  }
}

void secondLightChanged(uint8_t brightness)
{

  //Control the device
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R2, LOW);
      Serial.println("Device2 ON");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
    digitalWrite(R2, HIGH);
    Serial.println("Device2 OFF");
  }
}

void thirdLightChanged(uint8_t brightness)
{
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R3, LOW);
      Serial.println("Device3 ON");
      //Serial.print("ON, brightness ");
      //Serial.println(brightness);
    }
  }
  else
  {
    digitalWrite(R3, HIGH);
    Serial.println("Device3 ON");

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
      Serial.println("Device4 ON");

    }
  }
  //Serial.print("ON, brightness ");
  //Serial.println(brightness);
  else
  {
    digitalWrite(R4, HIGH);
    Serial.println("Device4 ON");

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
