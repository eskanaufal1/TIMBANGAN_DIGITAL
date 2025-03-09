void time_setup() {
  timeClient.begin();
}

void time_loop() {
  timeClient.update();
  //  Serial.print("Waktu = ");
  //  Serial.print(timeClient.getFormattedTime());
  //  Serial.print(" Tanggal = ");
  //  Serial.println(timeClient.getFormattedDate());
}
