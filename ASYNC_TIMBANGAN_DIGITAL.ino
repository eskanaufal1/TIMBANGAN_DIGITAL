// Menyertakan file header yang diperlukan
#include "GlobalVariable.h"   // Untuk variabel global
#include "LED.h"              // Untuk LED
//#include "SevenSegment.h"     // Untuk LED
#include "EEPROM_Func.h"      // Untuk EEPROM
#include "WebserverPico.h"    // Untuk Webserver
#include "Motor.h"            // untuk Motor
#include "WiFi.h"             // Untuk koneksi WiFi
#include "MQTT.h"             // Untuk komunikasi MQTT
#include "TimerInterval.h"    // Untuk koneksi WiFi
#include "CardReader.h"       // Untuk pembaca kartu
#include "Scale.h"            // Untuk pengaturan scale (misalnya load cell atau sensor)
//#include "Waktu.h"            // Untuk pengaturan waktu

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(2000);
  Serial.println("Starting. . .");
  EEPROM_SETUP();
  LED_setup();
  Webserver_setup();
  if (!WEBSERVER_STATE) {
    Serial.println("Normal Mode . . . ");
    dataForEEPROM();
    wifi_setup();
    mqtt_setup();
    PN532_setup();

    serial_read_setup();
    PN532_setup();
    motor_setup();
    timerInterval_setup();
  }
}

void machine_normalizer() {
  if ((millis() - initMachine) > 3000) {
    if (machineState == "VALIDATING" || machineState == "SPAMMING") {
      machineState = "AVL";
      initMachine = millis();
    }

  }
}

void loop() {
  if (WEBSERVER_STATE) {
    Webserver_loop();
  }
  if (!WEBSERVER_STATE) {
    LED_loop();
    PN532_loop();
    mqtt_loop();
    machine_normalizer();

    local_client.loop();
    serial_read_loop();
    timerInterval_loop();
  }
}

//void loop1() {
//  if (!WEBSERVER_STATE) {
//    local_client.loop();
//    serial_read_loop();
//    timerInterval_loop();
//  }
//}
