void reconnect_wifi() {
  int cw = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    LED_noWifi();
    delay(1000);
    if (cw >= 10) {
      rp2040.reboot();
    }
    cw++;
  }
}

void wifi_setup() {
  Serial.print("Setup wifi . . . ");
  WiFi.mode(WIFI_STA);
  //  WiFi.config(ip, dns, gateway, subnet);
  //  WiFi.config(ip);
  WiFi.begin(ssid, password);
  delay(1000);
  reconnect_wifi();
  //  WiFi.config(ip);
  Serial.println("");
  Serial.print("Pico W is connected to WiFi network ");
  Serial.println(WiFi.SSID());

  Serial.print("Assigned IP Address: ");
  Serial.println(WiFi.localIP());
}

void wifi_loop() {
  reconnect_wifi();
  if (Serial.readStringUntil('\n') == "IP") {
    Serial.print("Assigned IP Address: ");
    Serial.println(WiFi.localIP());
  }
}
