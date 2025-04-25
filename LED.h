void LED_setup() {
  pixels.begin();
  pixels.clear();
}

bool led_state = false;

void LED_noWifi() {
  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    pixels.show();   // Send the updated pixel colors to the hardware.
  }
  if (led_state == false) {
    pixels.clear();
    led_state != led_state;
  }
  else {
    led_state != led_state;
  }
}

void LED_NFC() {
  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    pixels.show();   // Send the updated pixel colors to the hardware.

    //    delay(1); // Pause before next pass through loop
  }
  if (led_state == false) {
    pixels.clear();
    led_state != led_state;
  }
  else {
    led_state != led_state;
  }
}

void LED_noMQTT() {
  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(128, 0, 128));
    pixels.show(); // Send the updated pixel colors to the hardware.
    // delay(1); // Pause before next pass through loop
  }
  if (led_state == false) {
    pixels.clear();
    led_state != led_state;
  }
  else {
    led_state != led_state;
  }
}

void LED_AVL() {
  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(255, 255, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    //    delay(1); // Pause before next pass through loop
  }
}

void LED_validating() {
  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(255, 69, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    //    delay(1); // Pause before next pass through loop
  }
}

void LED_validated() {
  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(255, 69, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    //    delay(1); // Pause before next pass through loop
  }
}

void LED_spamming() {
  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));

    pixels.show();   // Send the updated pixel colors to the hardware.

    //    delay(1); // Pause before next pass through loop
  }
}

void LED_loop() {
  if (machineState == "AVL"){
    LED_AVL();
  }
  if (machineState == "NOWIFI"){
    LED_noWifi();
  }
  if (machineState == "NOMQTT"){
    LED_noMQTT();
  }
  if (machineState == "VALIDATING"){
    LED_validating();
  }
  if (machineState == "VALIDATED"){
    LED_validated();
  }
  if (machineState == "SPAMMING"){
    LED_spamming();
  }
}
