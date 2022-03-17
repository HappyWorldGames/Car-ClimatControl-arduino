void showFanSpeedPID(){
  Serial.println("FanSpeedPID:");
  Serial.print("P ");
  Serial.println(setting.fanSpeedPID[0]);
  Serial.print("I ");
  Serial.println(setting.fanSpeedPID[1]);
  Serial.print("D ");
  Serial.println(setting.fanSpeedPID[2]);
}

void setSpeedFan(int speed, boolean absolute = false, boolean restart = false) {
  if(!absolute) speed = map(speed, 0, 100, 0, 255);
  speed = constrain(speed, !absolute ? setting.minSpeedFan : 0, 255);
  if (speedFan == speed && !absolute && !restart) return;

  speedFan = speed;
  if (speedFan == setting.minSpeedFan && !absolute && !setting.alwaysOnFan) speedFan = 0;

  Serial.print("SpeedFan_Set ");
  Serial.println(speedFan);

  analogWrite(TRANSISTOR_BUS, speedFan); //max 255
}

void getStatusControllFan() {
  Serial.print("SpeedFan_Set ");
  Serial.println(speedFan);
}
