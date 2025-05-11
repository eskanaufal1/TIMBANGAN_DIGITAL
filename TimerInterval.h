void callback_live_feed() {
  if (OutputInt > thresholdWeight) {
    weightSamples.add(OutputInt);
    live_feed(BraceletCode, machine_id, OutputInt, String(random(1,100)));
    Serial.println("SPAMMING - - - - - - - - - - - - - - - - -");
  }
}

void timerInterval_setup() {
  timer_live.register_callback(callback_live_feed);
}

void timerInterval_loop() {
  if (OutputInt >= thresholdWeight) {
    //    Serial.print("SPAMMING");
    machineState = "SPAMMING";
    timer_live.run(300);
  }
  else{
    machineState = "AVL";
  }
}
