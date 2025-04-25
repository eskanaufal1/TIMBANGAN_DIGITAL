void callback_live_feed() {
  if (OutputInt > 100) {
    weightSamples.add(OutputInt);
    live_feed(BraceletCode, machine_id, OutputInt, "0");
    Serial.println("SPAMMING - - - - - - - - - - - - - - - - -");
  }
}

void timerInterval_setup() {
  timer_live.register_callback(callback_live_feed);
}

void timerInterval_loop() {
  if (liveFeedStart == true) {
    machineState = "SPAMMING";
    timer_live.run(100);
    //callback_live_feed();
    if (weightSamples.isFull() == true || counterInterval >= 20) {
      reconnect();
      int fixOutput = weightSamples.getMedian();
      Serial.println("Sending Median . . . ");
      //      displayMedian(fixOutput);
      //      local_client.subscribe(topic, 0);
      send_fix_weight(BraceletCode, machine_id, fixOutput, "0");
      liveFeedStart = false;
      weightSamples.clear();
      Serial.println("Sending Median Done ");
      //      client.subscribe(topic);
      machineState = "AVL";
      Name = "";
    }
  }
}
