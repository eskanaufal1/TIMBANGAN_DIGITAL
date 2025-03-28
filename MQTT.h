
void reconnect() {
  // Loop until we're reconnected
  while (!local_client.connected()) {
    reconnect_wifi();
    Serial.print("Attempting MQTT connection to ");
    Serial.print(mqtt_local_server);
    Serial.print(" . . . .");
    // Attempt to connect
    if (local_client.connect(clientID, user, pass)) { //client.connect(clientID, user, pass) &&
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish(topic1, "hello world");
      // ... and resubscribe
      local_client.subscribe(topic);
      //      client.subscribe(topic2);
      //      client.subscribe(topic3);
      //      client.subscribe(topic4);
      Serial.print("Subscribed Server = ");
      Serial.println(topic);
    } else {
      Serial.print("failed, rc = ");
      Serial.print(local_client.state());
      Serial.println(" try again in 5 seconds");
      LED_noMQTT();
      // Wait 5 seconds before retrying
      delay(2000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  //  Serial.print("Message arrived [");
  //  Serial.print(topic);
  //  Serial.print("] ");
  //  for (int i = 0; i < length; i++) {
  //    Serial.print((char)payload[i]);
  //  }
  //  Serial.println();
  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, payload, length);
  if (err) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(err.c_str());
  } else {
    if (doc["action"] == "check-connection") {
      check_state = true;
    }
    if (doc["action"] == "scaling-weight-response") {
      bool machine_state = doc["status"];
      if (machine_state == true && actuator == false) {
        actuator = true;
        motor_run_loop();
        actuator = false;
      }
    }
  }
}

void checking_connection() {
  if (check_state == true) {
    //      reconnect();
    Serial.println("Checking status machine");
    JsonDocument doc;
    doc["action"] = "check-connection-response";
    doc["status"] = "true";
    doc["date_time"] = timeClient.getFormattedDate();
    char buff[128];

    size_t n = serializeJson(doc, buff);
    Serial.println(buff);
    // Send JSON to MQTT topic
    if (local_client.publish(topic, buff, n)) {
      Serial.println("JSON response sent to MQTT");
      check_state = false;
    } else {
      Serial.println("Failed to send JSON status to MQTT");
    }
  }
}

void machine_checking(String braceletCode) {
  Serial.println("Checking status machine");
  JsonDocument doc;
  doc["action"] = "machine-check";
  doc["braceletcode"] = braceletCode;
  doc["scalecode"] = topic;
  doc["date_time"] = timeClient.getFormattedDate();
  char buff[128];

  size_t n = serializeJson(doc, buff);
  Serial.println(buff);
  // Send JSON to MQTT topic
  if (local_client.publish(topic, buff, n)) {
    Serial.println("JSON response sent to MQTT");
    check_state = false;
  } else {
    Serial.println("Failed to send JSON status to MQTT");
  }

}

void send_fix_weight(String braceletcode, String machine_id, float weight, String id) {
  JsonDocument doc;

  /*  {
      action:"scaling-weight",
      braceletcode:"B4",
      scalecode:"SCALE-1",
      weightnumber:"200",
      uidreq:uuid.v1()
    }*/
  doc["action"] = "scaling-weight";
  doc["braceletcode"] = braceletcode;
  doc["scalecode"] = machine_id;
  doc["weightnumber"] = weight;
  doc["uidreq"] = id;
  reconnect();
  char buffer[256];
  size_t n = serializeJson(doc, buffer);
  Serial.println(buffer);

  // Send JSON to MQTT topic
  if (local_client.publish(topic, buffer, n)) {
    Serial.println("JSON sent to MQTT");
  } else {
    Serial.println("Failed to send JSON to MQTT");
  }
}

void live_feed(String braceletcode, String machine_id, float weight, String id) {
  JsonDocument doc;

  /*  {
      action:"scaling-weight",
      braceletcode:"B4",
      scalecode:"SCALE-1",
      weightnumber:"200",
      uidreq:uuid.v1()
    }*/
  doc["action"] = "scaling-weight";
  doc["braceletcode"] = braceletcode;
  doc["scalecode"] = machine_id;
  doc["weight"] = weight;
  doc["uidreq"] = id;
  reconnect();
  char buffer[128];
  size_t n = serializeJson(doc, buffer);
  Serial.println(buffer);

  // Send JSON to MQTT topic
  if (local_client.publish(topic, buffer, n)) {
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
  //  client.subscribe(topic1);
  //  client.subscribe(topic2);
  //  client.subscribe(topic3);
  //  client.subscribe(topic4);
}
