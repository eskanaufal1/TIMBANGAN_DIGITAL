
void reconnect() {
  // Loop until we're reconnected
  if (!local_client.connected()) {
    reconnect_wifi();
    Serial.print("Attempting MQTT connection to ");
    Serial.print(mqtt_local_server);
    Serial.print(" . . . .");
    long now = millis();
    // Attempt to connect
    if ((now - lastConnection) > 2000) {
      lastConnection = now;
      if (local_client.connect(clientID, user, pass)) { //client.connect(clientID, user, pass) &&
        Serial.println("connected");
        // Once connected, publish an announcement...
        local_client.subscribe(topic);
        Serial.print("Subscribed Server = ");
        Serial.println(topic);
        if (machineState != "VALIDATING" && machineState != "SPAMMING") {
          machineState = "AVL";
        }
      } else {
        Serial.print("failed, rc = ");
        Serial.print(local_client.state());
        Serial.println(" try again in 5 seconds");
        machineState = "NOMQTT";
        LED_noMQTT();
      }
    }
  }
  else {
    lastConnection = millis();
    local_client.loop();
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
  //  if (machineState != "SPAMMING") {
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
    //      if (doc["action"] == "check-bracelet-response" && doc["status"] == true && (lastVal - initVal) < 5000 && machineState == "VALIDATING") {
    //        validate = true;
    //        Name = String(doc["userdisplayname"]);
    //        machineState = "VALIDATED";
    //        LED_validated();
    //        Serial.println(String("UID Validated = ") + uid[0] + uid[1] + uid[2] + uid[3]);
    //        Serial.println(String("Name = ") + Name);
    //        // local_client.unsubscribe(topic);
    //      }
    if (doc["action"] == "check-bracelet-response" && doc["status"] == false) {
      machineState = "AVL";
    }
  }
  //  }
}

//void checking_connection() {
//  if (check_state == true) {
//    //      reconnect();
//    Serial.println("Checking status machine");
//    JsonDocument doc;
//    doc["action"] = "check-connection-response";
//    doc["status"] = "true";
//    doc["date_time"] = timeClient.getFormattedDate();
//    char buffer[128];
//
//    size_t n = serializeJson(doc, buffer);
//    Serial.println(buffer);
//    uint8_t uintdata[sizeof(buffer)];
//    memcpy(uintdata, buffer, sizeof(buffer));
//    // Send JSON to MQTT topic
//    if (local_client.publish(topic, uintdata, n, false))  {
//      Serial.println("JSON response sent to MQTT");
//      check_state = false;
//    } else {
//      Serial.println("Failed to send JSON status to MQTT");
//    }
//  }
//}

//void validate_bracelet(String braceletCode) {
//  Serial.println("Validate Bracelet");
//  JsonDocument doc;
//  doc["action"] = "check-bracelet";
//  doc["braceletcode"] = braceletCode;
//  doc["scalecode"] = topic;
//  //  doc["date_time"] = timeClient.getFormattedDate();
//  char buffer[128];
//
//  size_t n = serializeJson(doc, buffer);
//  Serial.println(buffer);
//  uint8_t uintdata[sizeof(buffer)];
//  memcpy(uintdata, buffer, sizeof(buffer));
//  // Send JSON to MQTT topic
//  if (local_client.publish(topic, uintdata, n, false))  {
//    Serial.println("JSON response sent to MQTT");
//    initVal = millis();
//  } else {
//    Serial.println("Failed to send JSON status to MQTT");
//  }
//}

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
  //  client.loop();
  local_client.loop();
}
