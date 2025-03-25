void displaySS(int number, int brightness = 15) {
  display.setBrightness(brightness);
  display.showNumberDec(number, false);
}
void SevenSetup() {
  display.clear();
}

void displayMedian(int number, int brightness = 15) {
  for (int i = 0; i < 5; i++) {
    display.setBrightness(brightness);
    display.showNumberDec(number, false);
    delay(700);
    display.clear();
    delay(300);
  }
}
