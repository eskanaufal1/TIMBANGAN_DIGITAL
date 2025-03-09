void motor_setup() {
  pinMode(RMotor, OUTPUT);
  pinMode(LMotor, OUTPUT);
}

void motor_run(bool dir, int pwm) {
  if (dir == false) {
    analogWrite(LMotor, pwm);
    analogWrite(RMotor, 0);
  }
  else {
    analogWrite(RMotor, pwm);
    analogWrite(LMotor, 0);
  }
}

void motor_run_loop() {
  Serial.println("Motor Naik . . . . . ");
  motor_run(false, 255);
  delay(35000);
  Serial.println("Motor Turun . . . . . ");
  motor_run(true, 255);
  delay(35000);
  motor_run(true, 0);
  Serial.println("Motor Selesai . . . . . ");
  digitalWrite(LED_BUILTIN, LOW);
}
