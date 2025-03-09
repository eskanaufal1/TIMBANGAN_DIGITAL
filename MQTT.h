
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(clientID, user, pass)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish(topic1, "hello world");
      // ... and resubscribe
      client.subscribe(topic1);
      client.subscribe(topic2);
      client.subscribe(topic3);
      client.subscribe(topic4);
      Serial.println("Subscribed 4 topic");
    } else {
      Serial.print("failed, rc = ");
      Serial.print(client.state());
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
    //    Serial.println(String("Topic = ") + topic);
    String topicString = topic;
    //    Serial.println(topicString == topic3);
    if ( topicString == topic3) {
      String machine_state = doc["status"];
      Serial.println("Checking status machine");
      if (machine_state) {
        JsonDocument doc;
        doc["status"] = true;
        reconnect();
        char buff[128];
        size_t n = serializeJson(doc, buff);
        Serial.println(buff);
        // Send JSON to MQTT topic
        if (client.publish(topic4, buff, n)) {
          Serial.println("JSON response sent to MQTT");
        } else {
          Serial.println("Failed to send JSON status to MQTT");
        }
      }
    }
    if (topicString == topic2) {
      bool machine_state = doc["status"];
      if (machine_state == true) {
        motor_run_loop();
      }
    }
  }
}

void ser(String braceletcode, String machine_id, String fishcode, float weight, String id) {
  JsonDocument doc;

  /*  {
      braceletcode:"B4",
      scalecode:"SCALE-1",
      fishcode:"FISH-1",
      weightnumber:"200",
      uidreq:uuid.v1()
    }*/
  doc["braceletcode"] = braceletcode;
  doc["scalecode"] = machine_id;
  doc["fishcode"] = fishcode;
  doc["weightmedian"] = weight;
  doc["uidreq"] = id;
  reconnect();
  char buffer[512];
  size_t n = serializeJson(doc, buffer);
  Serial.println(buffer);

  // Send JSON to MQTT topic
  if (client.publish(topic1, buffer, n)) {
    Serial.println("JSON sent to MQTT");
  } else {
    Serial.println("Failed to send JSON to MQTT");
  }
}

void live_feed(String braceletcode, String machine_id, String fishcode, float weight, String id) {
  JsonDocument doc;

  /*  {
      braceletcode:"B4",
      scalecode:"SCALE-1",
      fishcode:"FISH-1",
      weightnumber:"200",
      uidreq:uuid.v1()
    }*/
  doc["braceletcode"] = braceletcode;
  doc["scalecode"] = machine_id;
  doc["fishcode"] = fishcode;
  doc["weightnumber"] = weight;
  doc["uidreq"] = id;
  reconnect();
  char buffer[512];
  size_t n = serializeJson(doc, buffer);
  Serial.println(buffer);

  // Send JSON to MQTT topic
  if (client.publish(topic1, buffer, n)) {
    Serial.println("JSON sent to MQTT");
  } else {
    Serial.println("Failed to send JSON to MQTT");
  }
}

void mqtt_setup() {
  client.setServer(mqtt_server, port);
  client.setCallback(callback);
  reconnect();
}

void mqtt_loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  //  client.subscribe(topic1);
  //  client.subscribe(topic2);
  //  client.subscribe(topic3);
  //  client.subscribe(topic4);
}
