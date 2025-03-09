// Menyertakan file header yang diperlukan
#include "GlobalVariable.h"   // Untuk variabel global
#include "LED.h"              // Untuk LED
#include "Motor.h"            // untuk Motor
#include "MQTT.h"             // Untuk komunikasi MQTT
#include "TimerInterval.h"             // Untuk koneksi WiFi
#include "CardReader.h"       // Untuk pembaca kartu
#include "Scale.h"            // Untuk pengaturan scale (misalnya load cell atau sensor)
#include "Waktu.h"            // Untuk pengaturan waktu
#include "WiFi.h"             // Untuk koneksi WiFi

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(2000);
  Serial.println("Starting. . .");
  LED_setup();
  wifi_setup();
  mqtt_setup();
  PN532_setup();
  time_setup();
  serial_read_setup();
  PN532_setup();
  motor_setup();
}

void loop() {
  LED_loop();
  wifi_loop();
  mqtt_loop();
  serial_read_loop();
  time_loop();
  PN532_loop();
  timerInterval_setup();
}

void loop1() {
  timerInterval_loop();
}
