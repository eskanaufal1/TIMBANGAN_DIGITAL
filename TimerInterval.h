void callback_live_feed() {
  if (OutputInt > thresholdWeight) {
    weightSamples.add(OutputInt);
    live_feed(BraceletCode, machine_id, OutputInt, String(random(1, 100)));
    Serial.println("SPAMMING - - - - - - - - - - - - - - - - -");
  }
}

//void callback_status() {
//  Serial.println(String("Status = ") + machineState);
//}

void callback_ping() {
  send_ping();
}

void timerInterval_setup() {
  timer_ping.register_callback(callback_ping);
  timer_live.register_callback(callback_live_feed);
  //  timer_status.register_callback(callback_status);
}

void timerInterval_loop() {
  timer_ping.run(30000);
  //  timer_status.run(1000);
  if (machineState != "VALIDATING" && machineState != "NOWIFI" && machineState != "NOMQTT") {
    if (OutputInt >= thresholdWeight ) {
      //    Serial.print("SPAMMING");
      machineState = "SPAMMING";
      timer_live.run(500);
    }

    if (OutputInt < thresholdWeight ) {
      machineState = "AVL";
    }
  }
}
