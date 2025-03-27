void LED_setup() {
  pixels.begin();
  pixels.clear();
}

bool led_state = false;

void LED_noWifi() {
  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
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

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(255, 255, 0));
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

void LED_loop() {
  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    //    delay(1); // Pause before next pass through loop
  }

}
