
void reconnect() {
  // Loop until we're reconnected
  reconnect_wifi();
  while (!local_client.connected()) {
    machineState = "NOMQTT";
    Serial.print("Attempting MQTT connection to ");
    Serial.print(mqtt_local_server);
    Serial.print(" . . . .");
    // Attempt to connect

    if (local_client.connect(clientID, user, pass)) { //client.connect(clientID, user, pass) &&
      Serial.println("connected");
      // Once connected, publish an announcement...
      local_client.subscribe(topic);
      Serial.print("Subscribed Server = ");
      Serial.println(topic);
      if (machineState != "VALIDATING" || machineState != "SPAMMING") {
        machineState = "AVL";
      }
    } else {
      Serial.print("failed, rc = ");
      Serial.print(local_client.state());
      Serial.println(" try again in 5 seconds");
      machineState = "NOMQTT";
      LED_noMQTT();
      delay(2000);
    }

  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, payload, length);
  if (err) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(err.c_str());
  } else {
    if (doc["action"] == "scaling-weight-response") {
      bool machine_state = doc["status"];
      if (machine_state == true && actuator == false) {
        actuator = true;
        motor_run_loop();
        actuator = false;
      }
    }
    if (doc["action"] == "check-bracelet-response" && doc["status"] == false) {
      machineState = "AVL";
    }
  }
  //  }
}


void machine_checking(String braceletCode) {
  Serial.println("Checking status machine");
  JsonDocument doc;
  doc["action"] = "machine-check";
  doc["braceletcode"] = braceletCode;
  doc["scalecode"] = topic;
  //  doc["date_time"] = timeClient.getFormattedDate();
  char buffer[128];

  size_t n = serializeJson(doc, buffer);
  Serial.println(buffer);
  uint8_t uintdata[sizeof(buffer)];
  memcpy(uintdata, buffer, sizeof(buffer));
  // Send JSON to MQTT topic
  if (local_client.publish(topic, uintdata, n, false))  {
    Serial.println("JSON response sent to MQTT");
    check_state = false;
  } else {
    Serial.println("Failed to send JSON status to MQTT");
  }
}

void send_fix_weight(String braceletcode, String machine_id, float weight, String id) {
  JsonDocument doc;
  doc["action"] = "submit-weight";
  doc["braceletcode"] = braceletcode;
  doc["userdisplayname"] = Name;
  doc["scalecode"] = machine_id;
  doc["weightnumber"] = weight;
  doc["uidreq"] = id;
  reconnect();
  char buffer[256];
  size_t n = serializeJson(doc, buffer);
  Serial.println(buffer);
  uint8_t uintdata[sizeof(buffer)];
  memcpy(uintdata, buffer, sizeof(buffer));
  // Send JSON to MQTT topic
  if (local_client.publish(topic, uintdata, n, false))  {
    Serial.println("JSON sent to MQTT");
  } else {
    Serial.println("Failed to send JSON to MQTT");
  }
}

void send_ping() {
  JsonDocument doc;
  doc["action"] = "PING";
  reconnect();
  char buffer[256];
  size_t n = serializeJson(doc, buffer);
  Serial.println(buffer);
  uint8_t uintdata[sizeof(buffer)];
  memcpy(uintdata, buffer, sizeof(buffer));
  // Send JSON to MQTT topic
  if (local_client.publish(topic, uintdata, n, false))  {
    Serial.println("JSON sent to MQTT");
  } else {
    Serial.println("Failed to send JSON to MQTT");
  }
}

void live_feed(String braceletcode, String machine_id, float weight, String id) {
  JsonDocument doc;
  doc["action"] = "spamming-weight";
  doc["braceletcode"] = "";
  doc["userdisplayname"] = Name;
  doc["scalecode"] = machine_id;
  doc["weight"] = weight;
  doc["uidreq"] = id;
  reconnect();
  char buffer[256];
  size_t n = serializeJson(doc, buffer);
  Serial.println(buffer);
  uint8_t uintdata[sizeof(buffer)];
  memcpy(uintdata, buffer, sizeof(buffer));
  // Send JSON to MQTT topic
  if (local_client.publish(topic, uintdata, n, false)) {
    Serial.println("JSON sent to MQTT");
  } else {
    Serial.println("Failed to send JSON to MQTT");
  }
}

void mqtt_setup() {
  //  client.setServer(mqtt_public_server, port);
  //  client.setCallback(callback);
  local_client.setServer(mqtt_local_server, local_port);
  local_client.setCallback(callback);
  reconnect();
}

void mqtt_loop() {
  if (!local_client.connected()) { //!client.connected() ||
    reconnect();
  }
  local_client.loop();
}
