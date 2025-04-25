// Function to read settings from EEPROM
void readEEPROM() {
  EEPROM.begin(EEPROM_SIZE);
  for (int i = 0; i < 32; i++) wifi_ssid[i] = EEPROM.read(i);
  for (int i = 0; i < 64; i++) wifi_password[i] = EEPROM.read(32 + i);
  for (int i = 0; i < 64; i++) mqtt_server[i] = EEPROM.read(96 + i);
  mqtt_port = EEPROM.read(160) << 8 | EEPROM.read(161); // 2 bytes for port
  for (int i = 0; i < 32; i++) mqtt_username[i] = EEPROM.read(162 + i);
  for (int i = 0; i < 32; i++) mqtt_password[i] = EEPROM.read(194 + i);
  for (int i = 0; i < 64; i++) mqtt_topic[i] = EEPROM.read(226 + i);
}

// Function to save settings to EEPROM
void writeEEPROM() {
  EEPROM.begin(EEPROM_SIZE);
  for (int i = 0; i < 32; i++) EEPROM.write(i, wifi_ssid[i]);
  for (int i = 0; i < 64; i++) EEPROM.write(32 + i, wifi_password[i]);
  for (int i = 0; i < 64; i++) EEPROM.write(96 + i, mqtt_server[i]);
  EEPROM.write(160, mqtt_port >> 8); // 1st byte of port
  EEPROM.write(161, mqtt_port & 0xFF); // 2nd byte of port
  for (int i = 0; i < 32; i++) EEPROM.write(162 + i, mqtt_username[i]);
  for (int i = 0; i < 32; i++) EEPROM.write(194 + i, mqtt_password[i]);
  for (int i = 0; i < 64; i++) EEPROM.write(226 + i, mqtt_topic[i]);
  EEPROM.commit();
}


void EEPROM_SETUP() {
  EEPROM.begin(EEPROM_SIZE);
}

void dataForEEPROM() {
  readEEPROM();
  ssid = wifi_ssid;
  password = wifi_password;
  mqtt_local_server = mqtt_server;
  local_port = mqtt_port;
  user = mqtt_username;
  pass = mqtt_password;
  topic = clientID = mqtt_topic;
  machine_id = String(topic);
}
