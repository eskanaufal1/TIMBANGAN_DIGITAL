
void braceletCheck(String targetBracelet) {
  for (int i = 0; i < numberOfBracelets; i++) {
    if (braceletIDs[i] == targetBracelet) {  // Compare strings using strcmp
      match = true;
      break;
    }
    else {
      match = false;
    }
  }
  if (match) {
    Serial.println("Admin bracelet, sending machine checking. . . ");
    machine_checking(targetBracelet);
  }
}

void handleCardDetected() {
  uint8_t success = false;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  // read the NFC tag's info
  success = nfc.readDetectedPassiveTargetID(uid, &uidLength);
  Serial.println(success ? "Read successful" : "Read failed (not a card?)");

  if (success && liveFeedStart == false) {
    LED_NFC();
    // Display some basic information about the card
    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length: "); Serial.print(uidLength, DEC); Serial.println(" bytes");
    Serial.print("  UID Value: ");
    nfc.PrintHex(uid, uidLength);
    // Display some basic information about the card

    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length: ");
    Serial.print(uidLength, DEC);
    Serial.println(" bytes");
    Serial.print("  UID Value: ");
    char hexString[3 * uidLength + 1]; // Each byte will be 2 hex digits, plus 1 for null terminator

    for (int i = 0; i < uidLength; i++) {
      sprintf(hexString + (i * 2), "%02X", uid[i]);  // Convert each byte to 2 hex characters
    }
    nfc.PrintHex(uid, uidLength);
    delay(500);
    BraceletCode = hexString;
    braceletCheck(BraceletCode);
    if (!match) {
      liveFeedStart = true;
      local_client.unsubscribe(topic);
      Serial.println(String("UID = ") + uid[0] + uid[1] + uid[2] + uid[3]);
    }
    else {
      match = false;
    }
    timeLastCardRead = millis();
  }

  // The reader will be enabled again after DELAY_BETWEEN_CARDS ms will pass.
  readerDisabled = true;
}

void startListeningToNFC() {
  // Reset our IRQ indicators
  irqPrev = irqCurr = HIGH;

  Serial.println("Starting passive read for an ISO14443A Card ...");
  if (!nfc.startPassiveTargetIDDetection(PN532_MIFARE_ISO14443A)) {
    Serial.println("No card found. Waiting...");
  } else {
    Serial.println("Card already present.");
    handleCardDetected();
  }
}

void PN532_setup() {
  //  Serial.begin(115200);

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.'); Serial.println((versiondata >> 8) & 0xFF, DEC);

  startListeningToNFC();
}

void PN532_loop() {
  if (readerDisabled) {
    if (millis() - timeLastCardRead > DELAY_BETWEEN_CARDS) {
      readerDisabled = false;
      startListeningToNFC();
    }
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    irqCurr = digitalRead(PN532_IRQ);

    // When the IRQ is pulled low - the reader has got something for us.
    if (irqCurr == LOW && irqPrev == HIGH) {
      Serial.println("Got NFC IRQ");
      handleCardDetected();
    }
    irqPrev = irqCurr;
    digitalWrite(LED_BUILTIN, LOW);
  }
  //  Serial.println(".");
  //  delay(1000);

}
