
void braceletCheck(String targetBracelet) {
  for (int i = 0; i < numberOfBracelets; i++) {
    if (braceletIDs[i] == targetBracelet) {  // Compare strings using strcmp
      match = true;
      Serial.println("Admin bracelet, sending machine checking. . . ");
      machine_checking(targetBracelet);
      match = false;
      machineState = "AVL";
      liveFeedStart = false;
      break;
    }
    else {
      match = false;
    }
  }

  if (match == false) {
    initMachine = millis();
    machineState = "VALIDATING";
    Serial.println("VALIDATING");
    validate_bracelet(targetBracelet);
  }
}

void handleCardDetected() {
  // read the NFC tag's info
  success = nfc.readDetectedPassiveTargetID(uid, &uidLength);
  Serial.println(success ? "Read successful" : "Read failed (not a card?)");

  if (success && liveFeedStart == false) {
    //    liveFeedStart = true;
    //    LED_NFC();
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
