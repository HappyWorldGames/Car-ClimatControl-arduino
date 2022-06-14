boolean manualFanSpeed = false; // need save this
boolean manualServoHot = false;

void setManualFanSpeed(boolean manual){
  if(manualFanSpeed == manual) return;
  manualFanSpeed = manual;
  Serial.print("manualFanSpeed ");
  Serial.println(manualFanSpeed);
}
void setManualServoHot(boolean manual){
  if(manualServoHot == manual) return;
  manualServoHot = manual;
  Serial.print("manualServoHot ");
  Serial.println(manualServoHot);
}

//Прием команд в режиме auto
void serialAutoMode(int command) {
  switch (command) {
    case 01:
      setTemp(Serial.parseFloat());
      break;
    case 11:
      setManualFanSpeed(true);
      setSpeedFan(Serial.parseInt());
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
    case 13:
      setManualFanSpeed(false);
      break;
    case 22:
      setManualServoHot(true);
      setRotateServoHot(map(Serial.parseInt(), 0, 100, 0, setting.maxRotateServoHot));
      break;
    case 23:
      setManualServoHot(false);
      break;
  }
}
//Действия в режиме auto
void autoMode() {
  static uint32_t tmr;
  static byte servoTick = 0;
  if (millis() - tmr < setting.AUTO_MODE_UPDATE_TIME) return;
  tmr = millis();
  servoTick++;

  getTemp();
  if(!manualFanSpeed) {
    if (setting.tempSet > tempNowCar && tempNowHeater < setting.tempMinStartWork){
      if(speedFan > 0) setSpeedFan(0, true);
      return;
    }
    //Максимальные обороты вентилятора
    int maxSpeedFan = setting.tempSet < tempNowCar ? 100 : map(tempNowHeater, setting.tempMinStartWork, setting.tempMinStartWork + setting.tempMaxStartWork, 0, 100);
    maxSpeedFan = constrain(maxSpeedFan, 0, 100);
    
    //Разница температуры от заданной
    float diffTemp = abs(setting.tempSet - tempNowCar);
  
    //Вентилятор
    int localSpeedFan;
    if(setting.fanSpeedType == 0){
      int diffSpeedFan = maxSpeedFan - setting.minSpeedFan;
      int localMinFanSpeed = setting.minSpeedFan - diffSpeedFan;
      
      fanSpeedPID.setLimits(localMinFanSpeed, maxSpeedFan);
      fanSpeedPID.input = (int)tempNowCar;
      fanSpeedPID.getResult();
      if(setting.minSpeedFan <= fanSpeedPID.output) localSpeedFan = fanSpeedPID.output;
      else localSpeedFan = map(fanSpeedPID.output, localMinFanSpeed, setting.minSpeedFan, maxSpeedFan, setting.minSpeedFan);
    }else localSpeedFan = map(diffTemp, 0, setting.diffSpeedFan, 0, maxSpeedFan);
    localSpeedFan = constrain(localSpeedFan, 0, maxSpeedFan);
    setSpeedFan(localSpeedFan);
  }
  if(!manualServoHot && servoTick >= setting.servoTickCount){
    servoTick = 0;
    if(abs(setting.tempSet - tempNowCar) > setting.deadRotateServoHot){
      //Тепло-холод
      servoHotPID.setDt(setting.AUTO_MODE_UPDATE_TIME * setting.servoTickCount);
      servoHotPID.input = tempNowCar;
      servoHotPID.getResult();
      setRotateServoHot(servoHotPID.output);
    }
  }
  //Управление рекупирацией и кондиционером
  if(digitalRead(BUTTON_AIR_RECIRCULATION_BUS) == HIGH) airRecirculation(true);
  else if(digitalRead(BUTTON_AIR_RECIRCULATION_BUS) == LOW && digitalRead(BUTTON_AIR_CONDITIONING_BUS) == LOW) airRecirculation(false);
  if(setting.tempSet < tempNowCar && tempNowOutCar > setting.tempSet && digitalRead(BUTTON_AIR_CONDITIONING_BUS) == HIGH && speedFan > 0){
    airConditioning(true);
    airRecirculation(true);
  }else airConditioning(false);
}

void getStatusModeAuto(){
  Serial.print("manualFanSpeed ");
  Serial.println(manualFanSpeed);

  Serial.print("manualServoHot ");
  Serial.println(manualServoHot);
}
