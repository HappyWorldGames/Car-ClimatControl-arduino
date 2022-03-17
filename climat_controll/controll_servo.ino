void initControllServo(){
  servoHot.setSpeed(50);   // ограничить скорость
  servoHot.setAccel(0.3);    // установить ускорение (разгон и торможение)

  servoHot.attach(SERVO_BUS); //привязываем привод к порту
}

void showServoHotPID(){
  Serial.println("ServoHotPID:");
  Serial.print("P ");
  Serial.println(setting.servoHotPID[0]);
  Serial.print("I ");
  Serial.println(setting.servoHotPID[1]);
  Serial.print("D ");
  Serial.println(setting.servoHotPID[2]);
}

void setRotateServoHot(int rotate, boolean absolute = false) {
  if (rotateServoHot == rotate && !absolute) return;

  if (!absolute){
    rotateServoHot = map(rotate, SERVO_ROTATE_MIN, SERVO_ROTATE_MAX, 0, setting.maxRotateServoHot);
    rotateServoHot = constrain(rotateServoHot, SERVO_ROTATE_MIN, SERVO_ROTATE_MAX);
  }else rotateServoHot = rotate;

  Serial.print("ServoHot_Set ");
  Serial.println(rotateServoHot);

  servoHot.setTargetDeg(rotateServoHot);
}

void setRotateServoAirWay(int rotate, boolean absolute = false) {
  if (rotateServoHot == rotate && !absolute) return;

  if (!absolute){
    rotateServoHot = map(rotate, SERVO_ROTATE_MIN, SERVO_ROTATE_MAX, 0, setting.maxRotateServoHot);
    rotateServoHot = constrain(rotateServoHot, SERVO_ROTATE_MIN, SERVO_ROTATE_MAX);
  }else rotateServoHot = rotate;

  Serial.print("ServoHot_Set ");
  Serial.println(rotateServoHot);

  servoHot.setTargetDeg(rotateServoHot);
}

void getStatusControllServo() {
  Serial.print("ServoHot_Set ");
  Serial.println(rotateServoHot);
}
