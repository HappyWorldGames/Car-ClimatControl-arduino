#include <ServoSmooth.h>

class TempServoController {
  private:
    int servoPos = -1;
    int maxPosition = 180;
    ServoSmooth tempServo; //контроль заслонки тепло-хoлод
    
  public:
    ServoController(int tempServoPin, int servoPos = 0) {
      tempServo.setSpeed(50);   // ограничить скорость
      tempServo.setAccel(0.3);    // установить ускорение (разгон и торможение)
	  setServoPos(servoPos);
      tempServo.attach(tempServoPin); //привязываем привод к порту
	  setServoPos(servoPos);
    }

    void setServoPos(int position) {
      position = constrain(position, 0, 100);
      position = map(position, 0, 100, 0, maxPosition);

      servoPos = position;
      
      tempServo.setTargetDeg(servoPos);
    }

    void printServoPos() {
      int servoPosValue = map(servoPos, 0, maxPosition, 0, 100);
      
      Serial.print("temp_servo_pos=");
      Serial.println(servoPosValue);
    }
};
