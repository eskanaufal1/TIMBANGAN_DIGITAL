

// Function to handle the root page (form to input settings)
void handleRoot() {
  String html = "<html><body><h1>Configure MQTT and Wi-Fi</h1>";
  html += "<form action='/save' method='POST'>";
  html += "Wi-Fi SSID: <input type='text' name='wifi_ssid' value='" + String(wifi_ssid) + "'><br>";
  html += "Wi-Fi Password: <input type='text' name='wifi_password' value='" + String(wifi_password) + "'><br>";
  html += "MQTT Server: <input type='text' name='mqtt_server' value='" + String(mqtt_server) + "'><br>";
  html += "MQTT Port: <input type='text' name='mqtt_port' value='" + String(mqtt_port) + "'><br>";
  html += "MQTT Username: <input type='text' name='mqtt_username' value='" + String(mqtt_username) + "'><br>";
  html += "MQTT Password: <input type='text' name='mqtt_password' value='" + String(mqtt_password) + "'><br>";
  html += "MQTT Topic: <input type='text' name='mqtt_topic' value='" + String(mqtt_topic) + "'><br>";
  html += "Minimum Weight: <input type='text' name='weight_threshold' value='" + String(weight_threshold) + "'><br>";
  html += "<input type='submit' value='Save'>";
  html += "</form></body></html>";
  server.send(200, "text/html", html);
}

// Function to save settings from the form and restart
void handleSave() {
  String mqtt_server_input = server.arg("mqtt_server");
  String mqtt_port_input = server.arg("mqtt_port");
  String mqtt_username_input = server.arg("mqtt_username");
  String mqtt_password_input = server.arg("mqtt_password");
  String mqtt_topic_input = server.arg("mqtt_topic");
  String wifi_ssid_input = server.arg("wifi_ssid");
  String wifi_password_input = server.arg("wifi_password");
  String weight_threshold_input = server.arg("weight_threshold");

  // Store the new values
  wifi_ssid_input.toCharArray(wifi_ssid, sizeof(wifi_ssid));
  wifi_password_input.toCharArray(wifi_password, sizeof(wifi_password));
  mqtt_server_input.toCharArray(mqtt_server, sizeof(mqtt_server));
  mqtt_port = mqtt_port_input.toInt();
  mqtt_username_input.toCharArray(mqtt_username, sizeof(mqtt_username));
  mqtt_password_input.toCharArray(mqtt_password, sizeof(mqtt_password));
  mqtt_topic_input.toCharArray(mqtt_topic, sizeof(mqtt_topic));
  weight_threshold = weight_threshold_input.toInt();
  
  // Save to EEPROM
  writeEEPROM();

  // Restart to apply changes
  String html = "<html><body><h1>Configure MQTT and Wi-Fi</h1>";
  html += "<p><strong>Wi-Fi SSID:</strong> " + String(wifi_ssid) + "</p>";
  html += "<p><strong>Wi-Fi Password:</strong> " + String(wifi_password) + "</p>";
  html += "<p><strong>MQTT Server:</strong> " + String(mqtt_server) + "</p>";
  html += "<p><strong>MQTT Port:</strong> " + String(mqtt_port) + "</p>";
  html += "<p><strong>MQTT Username:</strong> " + String(mqtt_username) + "</p>";
  html += "<p><strong>MQTT Password:</strong> " + String(mqtt_password) + "</p>";
  html += "<p><strong>MQTT Topic:</strong> " + String(mqtt_topic) + "</p>";
  html += "<p><strong>Minimum Weight:</strong> " + String(weight_threshold) + "</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
  delay(2000);
  rp2040.restart();
}

void Webserver_setup() {
  //  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // DONT FOPRGET ADD IF CONDITIONS
  pinMode (WEBSERVER_PIN, INPUT_PULLUP);
  if (digitalRead(WEBSERVER_PIN) == LOW) {
    WEBSERVER_STATE = true;
  }
  if (WEBSERVER_STATE == true) {
    Serial.println("WEBSERVER MODE . . . ");
    readEEPROM();
    // Set up the Pico W in AP mode
    WiFi.mode(WIFI_AP);
    WiFi.softAP(apSSID, apPassword);
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Set up the web server
    server.on("/", HTTP_GET, handleRoot);
    server.on("/save", HTTP_POST, handleSave);

    // Start the server
    server.begin();
    Serial.println("Server started");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    ssid = wifi_ssid;
    password = wifi_password;
    mqtt_local_server = mqtt_server;
    local_port = mqtt_port;
    user = mqtt_username;
    pass = mqtt_password;
    topic = clientID = mqtt_topic;
    thresholdWeight = weight_threshold;
    machine_id = String(topic);

    // Print each variable to the Serial Monitor
    Serial.print("Wi-Fi SSID: ");
    Serial.print(wifi_ssid);
    Serial.println(";");

    Serial.print("Wi-Fi Password: ");
    Serial.print(wifi_password);
    Serial.println(";");

    Serial.print("MQTT Server: ");
    Serial.print(mqtt_server);
    Serial.println(";");

    Serial.print("MQTT Port: ");
    Serial.print(mqtt_port);
    Serial.println(";");

    Serial.print("MQTT Username: ");
    Serial.print(mqtt_username);
    Serial.println(";");

    Serial.print("MQTT Password: ");
    Serial.print(mqtt_password);
    Serial.println(";");

    Serial.print("MQTT Topic: ");
    Serial.print(mqtt_topic);
    Serial.println(";");

    Serial.print("Minimum Weight: ");
    Serial.print(thresholdWeight);
    Serial.println(";");
  }
}

//void display_seven() {
//  IPAddress localIp = WiFi.localIP();
//  for (int i = 0; i < 4; i++) {
//    displaySS(localIp[i]);
//    delay(1000);
//  }
//}

void Webserver_loop() {
  server.handleClient();
}

//void Webserver_loop1() {
//  display_seven();
//}
