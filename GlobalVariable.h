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
//#include "credentials.h"
#include <TM1637Display.h>

// Seven Segments connection pins (Digital Pins)
#define CLK 11
#define DIO 12
TM1637Display display(CLK, DIO);

// Interval Callback
bool liveFeedStart = false;
Simpletimer timer_live{};

//Bracelet var
String BraceletCode;
String braceletIDs[] = {
  "9E4866BB", "DED8B62B", "4EA8B32B", "CE6E79BB", "FAE70766", 
  "8E54B72B", "BE16B92B", "DE6DAF2B", "9EEFB72B", "EE9DB12B"
};
int numberOfBracelets = sizeof(braceletIDs) / sizeof(braceletIDs[0]);
bool match = false;

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
#define PIN       27
#define NUMPIXELS 75 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Pin Webserver
const int WEBSERVER_PIN = 26;
bool WEBSERVER_STATE = false;

// Weight sensor output variable
float Output;
int OutputInt;

// Wifi
char* ssid;
char* password;


//MQTT
char* mqtt_public_server;
char* mqtt_local_server;
//int port = 52023;
int port = 52043;
int local_port = 1883;
//int port = 1883;
//const char* topic1 = "scaling-weight";
//const char* topic2 = "scaling-weight-response";
//const char* topic3 = "check-connection";
//const char* topic4 = "check-connection-response";
char* clientID;
char* topic = clientID;
//const char* topic1 = "flush-test";
char* user;
char* pass;

//machine_id
String machine_id = String(topic);

//WiFiClient clients;
WiFiClient clients_local;

//PubSubClient client(clients);
PubSubClient local_client(clients_local);

//actuator
bool actuator = false;
#define RMotor (20)
#define LMotor (21)

//Webserver
#include <WebServer.h>
// Define AP credentials
const char* apSSID = "PicoW_Config";
const char* apPassword = "config1234";

//Check Status
bool check_state = false;

// Wi-Fi and MQTT Settings
char wifi_ssid[32];
char wifi_password[64];
char mqtt_server[64];
int mqtt_port = 1883;
char mqtt_username[32];
char mqtt_password[32];
char mqtt_topic[64];

// Initialize the web server on port 80
WebServer server(80);

#include <EEPROM.h>
#define EEPROM_SIZE 512 // Adjust size as necessary
