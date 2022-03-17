//Прием команд в режиме service
void serialServiceMode(int command) {
  switch (command) {
    //вентилятор
    case 11:
      setSpeedFan(Serial.parseInt(), true);
      break;
    case 12:
      setSpeedFan(map(Serial.parseInt(), 0, 100, setting.minSpeedFan, 255));
      break;
    case 13:
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
    case 14:
      setting.minSpeedFan = Serial.parseInt();
      Serial.print("minSpeedFan ");
      Serial.println(setting.minSpeedFan);
      break;
    //тепло-холод
    case 21:
      setRotateServoHot(Serial.parseInt(), true);
      break;
    case 22:
      setRotateServoHot(map(Serial.parseInt(), 0, 100, 0, setting.maxRotateServoHot));
      break;
    case 23:
      servoHot.setTarget(Serial.parseInt());
      Serial.print("write_servo_micro ");
      Serial.println(servoHot.getTarget());
      break;
    case 24:
      setting.maxRotateServoHot = Serial.parseInt();
      Serial.print("maxRotateServoHot ");
      Serial.println(setting.maxRotateServoHot);
      break;
    case 25:
      setting.deadRotateServoHot = Serial.parseFloat();
      Serial.print("deadRotateServoHot ");
      Serial.println(setting.deadRotateServoHot);
      break;
    //направление потока воздуха
    case 31:
      setRotateServoAirWay(Serial.parseInt(), true);
      break;
    case 32:
      setRotateServoAirWay(map(Serial.parseInt(), 0, 100, 0, setting.maxRotateServoHot));
      break;
    case 33:
      servoHot.setTarget(Serial.parseInt());
      Serial.print("write_servo_micro ");
      Serial.println(servoHot.getTarget());
      break;
    /*case 34:
      setting.maxRotateServoAirWay = Serial.parseInt();
      Serial.print("maxRotateServoAirWay ");
      Serial.println(setting.maxRotateServoAirWay);
      break;*/
    //Температура
    case 41:
      getTemp();
      break;
    case 42:
      setting.tempMinStartWork = Serial.parseInt();
      Serial.print("tempMinStartWork ");
      Serial.println(setting.tempMinStartWork);
      break;
    case 43:
      setting.tempMaxStartWork = Serial.parseInt();
      Serial.print("tempMaxStartWork ");
      Serial.println(setting.tempMaxStartWork);
      break;
    case 44:
      setting.diffSpeedFan = Serial.parseInt();
      Serial.print("diffSpeedFan ");
      Serial.println(setting.diffSpeedFan);
      break;
    case 45:
      tempNowHeater = Serial.parseFloat();
      Serial.print("tempNowHeater ");
      Serial.println(tempNowHeater);
      break;
    case 46:
      tempNowCar = Serial.parseFloat();
      Serial.print("tempNowCar ");
      Serial.println(tempNowCar);
      break;
    case 47:
      tempNowOutCar = Serial.parseFloat();
      Serial.print("tempNowOutCar ");
      Serial.println(tempNowOutCar);
      break;
    //Прочее
    case 51:
      setting.AUTO_MODE_UPDATE_TIME = Serial.parseInt();
      servoHotPID.setDt(setting.AUTO_MODE_UPDATE_TIME * setting.servoTickCount);
      fanSpeedPID.setDt(setting.AUTO_MODE_UPDATE_TIME);
      Serial.print("AUTO_MODE_UPDATE_TIME ");
      Serial.println(setting.AUTO_MODE_UPDATE_TIME);
      break;
    case 52:
      switch(Serial.parseInt()){
        case 0:
          setting.servoHotPID[0] = Serial.parseFloat();
          setting.servoHotPID[1] = Serial.parseFloat();
          setting.servoHotPID[2] = Serial.parseFloat();
          showServoHotPID();
          break;
        case 1:
          setting.fanSpeedPID[0] = Serial.parseFloat();
          setting.fanSpeedPID[1] = Serial.parseFloat();
          setting.fanSpeedPID[2] = Serial.parseFloat();
          showFanSpeedPID();
          break;
      }
      updatePID();
      break;
    case 53:
      switch(Serial.parseInt()){
        case 0:
          showServoHotPID();
          break;
        case 1:
          showFanSpeedPID();
          break;
      }
      break;
    case 54:
      setting.servoTickCount = Serial.parseInt();
      Serial.print("servoTickCount ");
      Serial.println(setting.servoTickCount);
      break;
    case 55:
      setting.fanSpeedType = Serial.parseInt();
      Serial.print("fanSpeedType ");
      Serial.println(setting.fanSpeedType);
      break;
    default:
      Serial.print("command '");
      Serial.print(command);
      Serial.println("' not found");
      break;
  }
}
//Действия в режиме service
void serviceMode() {
  airRecirculation(digitalRead(BUTTON_AIR_RECIRCULATION_BUS));
  airConditioning(digitalRead(BUTTON_AIR_CONDITIONING_BUS));
}

void getStatusModeService() {
  
}
