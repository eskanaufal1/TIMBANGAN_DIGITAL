void callback_live_feed() {
  live_feed(BraceletCode, machine_id, fishCode, Output, timeClient.getFormattedDate());
  weightSamples.add(Output);
}

void timerInterval_setup() {
  timer_live.register_callback(callback_live_feed);
}

void timerInterval_loop() {
  if (liveFeedStart == true) {
    timer_live.run(150);
    if (weightSamples.isFull() == true) {
      float fixOutput = weightSamples.getMedian();
      ser(BraceletCode, machine_id, fishCode, Output, timeClient.getFormattedDate());
      liveFeedStart = false;
      weightSamples.clear();
    }
  }
}
