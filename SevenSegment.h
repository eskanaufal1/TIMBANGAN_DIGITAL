//void displayNumber(int num) {
//  int digits[4];
//  digits[0] = num / 1000;
//  digits[1] = (num / 100) % 10;
//  digits[2] = (num / 10) % 10;
//  digits[3] = num % 10;
//
//  for (int i = 0; i < 4; i++) {
//    lc.setDigit(0, 3 - i, digits[i], false);
//  }
//}

void displaySS(int number) {
  //  displayNumber(number);
  display.clear();
  display.setBrightness(15);
  display.showNumberDec(0, false); // Expect: ___0
}

void SevenSetup() {
  //  /*
  //    The MAX72XX is in power-saving mode on startup,
  //    we have to do a wakeup call
  //  */
  //  lc.shutdown(0, false);
  //  /* Set the brightness to a medium values */
  //  lc.setIntensity(0, 8);
  //  /* and clear the display */
  //  lc.clearDisplay(0);
  display.clear();
  display.setBrightness(15);
}

void displayMedian(int number) {
  for (int i = 0; i < 5; i++) {
    displaySS(number);
    delay(700);
    //    lc.clearDisplay(0);
    display.clear();
    delay(300);
  }
}
