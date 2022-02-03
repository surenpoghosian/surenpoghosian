#define NUMPIXELS 35
#define R1 2
#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>

//WiFi.mode(WIFI_AP);
//WiFi.softAP("Teslight","123456789");
int status = WL_IDLE_STATUS;
char ssid[] = "ICN_000264"; //  your network SSID (name)
char pass[] = "83bjd86f2v";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)
bool relay = false;

unsigned int localPort = 2390;      // local port to listen on

uint8_t packetBuffer[255]; //buffer to hold incoming packet
//char  ReplyBuffer[] = "acknowledged";// a string to send back
uint8_t ReplyBuffer1[] = {72, 101, 108, 108, 111};

String b;

//IPAddress local_IP(192, 168, 1, 54);
//IPAddress gateway(192, 168, 1, 1);


WiFiUDP Udp;
Adafruit_NeoPixel strip (NUMPIXELS, R1, NEO_GRB + NEO_KHZ800);

void setup() {

  strip.begin();


  pinMode(R1, OUTPUT);
  strip.setBrightness(255);
  //Initialize serial and wait for port to open:

  Serial.begin(9600);

  while (!Serial) {

    ; // wait for serial port to connect. Needed for native USB port only

  }


  // attempt to connect to Wifi network:

  while (status != WL_CONNECTED) {

    Serial.print("Attempting to connect to SSID: ");

    Serial.println(ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:

    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:

    delay(10000);

  }

  Serial.println("Connected to wifi");

  printWifiStatus();

  Serial.println("\nStarting connection to server...");

  // if you get a connection, report back via serial:

  Udp.begin(localPort);
}

void loop() {



  // if there's data available, read a packet

  int packetSize = Udp.parsePacket();

  if (packetSize) {

    Serial.print("Received packet of size ");

    Serial.println(packetSize);

    Serial.print("From ");

    IPAddress remoteIp = Udp.remoteIP();

    Serial.print(remoteIp);

    Serial.print(", port ");

    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer

    int len = Udp.read(packetBuffer, 255);

    if (len > 0) {

      packetBuffer[len] = 0;

    }

    
    for (int i = 0; i < NUMPIXELS; i++) {

      strip.setPixelColor(i, strip.Color(packetBuffer[1], packetBuffer[2], packetBuffer[3]));
      delay(10);
      strip.show();
      
    }



    Serial.println("Contents:");



    // send a reply, to the IP address and port that sent us the packet we received

    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());

    Udp.write(ReplyBuffer1[0]);
    Udp.write(ReplyBuffer1[1]);
    Udp.write(ReplyBuffer1[2]);
    Udp.write(ReplyBuffer1[3]);
    Udp.write(ReplyBuffer1[4]);

    Udp.endPacket();

  }
}

void printWifiStatus() {

  // print the SSID of the network you're attached to:

  Serial.print("SSID: ");

  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:

  IPAddress ip = WiFi.localIP();

  Serial.print("IP Address: ");

  Serial.println(ip);

  // print the received signal strength:

  long rssi = WiFi.RSSI();

  Serial.print("signal strength (RSSI):");

  Serial.print(rssi);

  Serial.println(" dBm");
}
