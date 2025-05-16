void serial_read_setup() {
  mySerial.begin(9600);  //pin 8 TX, pin 9 RX
}

void serial_read_loop() {
//  mySerial.begin(9600);
  if (mySerial.available() > 0) {
    String input = mySerial.readStringUntil('\n');
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
    if (OutputInt >= 10000) {
      OutputInt = 0;
    } 

  }
}
