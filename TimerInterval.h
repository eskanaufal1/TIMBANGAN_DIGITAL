void callback_live_feed() {

  live_feed(BraceletCode, machine_id, OutputInt, timeClient.getFormattedDate());
  weightSamples.add(OutputInt);
  displaySS(OutputInt, 15);

  //  randomSeed(analogRead(0));
  //  int randomNumb = random(200);
  //  live_feed(BraceletCode, machine_id, randomNumb, timeClient.getFormattedDate());
  //  weightSamples.add(randomNumb);
  //  displaySS(randomNumb, 15);

}

void timerInterval_setup() {
  timer_live.register_callback(callback_live_feed);
}

void timerInterval_loop() {
  if (liveFeedStart == true) {
    timer_live.run(100);
    //    callback_live_feed();
    if (weightSamples.isFull() == true) {
      int fixOutput = weightSamples.getMedian();
      Serial.println("Sending Median . . . ");
      send_fix_weight(BraceletCode, machine_id, fixOutput, timeClient.getFormattedDate());
      delay(200);
      send_fix_weight(BraceletCode, machine_id, fixOutput, timeClient.getFormattedDate());
      displayMedian(fixOutput, 15);
      liveFeedStart = false;
      weightSamples.clear();
      Serial.println("Sending Median Done ");
      //      client.subscribe(topic);
      local_client.subscribe(topic);
    }
  }
}
