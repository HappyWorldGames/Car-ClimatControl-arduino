//Прием команд в режиме manual
void serialManualMode(int command) {
  switch (command) {
    case 11:
      setSpeedFan(map(Serial.parseInt(), 0, 100, setting.minSpeedFan, 255));
      break;
    case 12:
      switch (Serial.parseInt()) {
        case 0:
          setting.alwaysOnFan = false;
          break;
        case 1:
          setting.alwaysOnFan = true;
          break;
      }
      setSpeedFan(speedFan, false, true);
      Serial.print("AlwaysOnFan ");
      Serial.println(setting.alwaysOnFan);
      break;
    case 22:
      setRotateServoHot(map(Serial.parseInt(), 0, 100, 0, setting.maxRotateServoHot));
      break;
  }
}
//Действия в режиме manual
void manualMode() {
  static uint32_t tmr;
  if (millis() - tmr < setting.AUTO_MODE_UPDATE_TIME) return;
  tmr = millis();

  getTemp();
  airRecirculation(digitalRead(BUTTON_AIR_RECIRCULATION_BUS));
  airConditioning(digitalRead(BUTTON_AIR_CONDITIONING_BUS));
}

void getStatusModeManual() {
  
}
