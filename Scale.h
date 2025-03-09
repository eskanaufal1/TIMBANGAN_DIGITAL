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
    Serial.print("Data =");
    Serial.print(raw);
    int sIndex = raw.lastIndexOf('\r') - 4;
    int lIndex = raw.lastIndexOf('\r');
    String OutputF = raw.substring(sIndex, lIndex);
    Output = OutputF.toFloat();
    
    Serial.println(String(" Output = ") + OutputF + " Float = " + OutputF.toFloat());
    delay(100);
  }
}

void send_scale_live() {

}
