#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <Adafruit_NeoPixel.h>
#include <RunningMedian.h>
#include "Simpletimer.h"
#include "credentials.h"

// Interval Callback
bool liveFeedStart = false;
Simpletimer timer_live{};

//Bracelet var
String BraceletCode;

// Find Median
RunningMedian weightSamples = RunningMedian(50);  // jumlah median

// time
WiFiUDP ntpUDP;
const char* ntpServer = "pool.ntp.org";
// const long  gmtOffset_sec = 0;
// const int   daylightOffset_sec = 3600;
NTPClient timeClient(ntpUDP, ntpServer, 3600, 60000);

// If using the breakout or shield with I2C, define just the pins connected
// to the IRQ and reset lines.  Use the values below (2, 3) for the shield!
#define PN532_IRQ   (2)
#define PN532_RESET (3)  // Not connected by default on the NFC Shield

const int DELAY_BETWEEN_CARDS = 1500;
long timeLastCardRead = 0;
boolean readerDisabled = false;
int irqCurr;
int irqPrev;

// This example uses the IRQ line, which is available when in I2C mode.
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

// Neopixel LED
#define PIN       26
#define NUMPIXELS 75 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Weight sensor output variable
float Output;

// Wifi
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;


IPAddress ip(192, 168, 2, 105);
IPAddress dns(8, 8, 8, 8);
IPAddress gateway(192, 168, 2, 1);
IPAddress subnet(255, 255, 255, 0);

//machine_id
String machine_id = "SCALE-3";
String fishCode = "FISH-1";

//MQTT
const char* mqtt_server = MQTT_SERVER;
int port = 52023;
//int port = 1883;
//const char* topic1 = "scaling-weight";
const char* topic1 = "flush-test";
const char* topic2 = "scaling-weight-response";
const char* topic3 = "check-connection";
const char* topic4 = "check-connection-response";
const char* clientID = "SCALE-3";
const char* user = MQTT_USER;
const char* pass = MQTT_PASSWORD;


WiFiClient clients;
PubSubClient client(clients);

//actuator
bool actuator = false;
#define RMotor (20)
#define LMotor (21)
