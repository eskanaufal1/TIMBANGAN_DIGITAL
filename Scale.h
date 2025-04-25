void serial_read_setup() {
  Serial2.begin(9600);  //pin 8 TX, pin 9 RX
}

void serial_read_loop() {
  if (Serial2.available() > 0) {
    String input = Serial2.readStringUntil('\n');
    int startIndex = 0;
    while (startIndex < input.length() && input[startIndex] == '=') {
      startIndex++;
    }
    String raw = input.substring(startIndex);
    // Serial.print("Data =");
    // Serial.print(raw);
    int sIndex = raw.lastIndexOf('\r') - 5;
    int lIndex = raw.lastIndexOf('\r');
    String OutputF = raw.substring(sIndex, lIndex);
    Output = OutputF.toFloat();
    OutputInt = Output * 1000;
    if (OutputInt <= 0) {
      OutputInt = 0;
    }
    //    if (!liveFeedStart && OutputInt >= 100) {
    //      displaySS(OutputInt);
    //    }
    if (!liveFeedStart && OutputInt <= 100) {
      //      lc.clearDisplay(0);
      display.clear();
    }

    //    Serial.println(String(" Output = ") + OutputF + " Float = " + OutputF.toFloat());
    //    delay(100);
  }
}
