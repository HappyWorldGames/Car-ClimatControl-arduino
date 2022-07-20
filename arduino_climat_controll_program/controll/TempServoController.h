#pragma once

#include <ServoSmooth.h>

class TempServoController {
	private:
		Setting *setting = NULL;
		int servoPos = -1;
		int maxPosition = 180;
		ServoSmooth tempServo; //контроль заслонки тепло-хoлод
		
	public:
		TempServoController(int tempServoPin, Setting setting = Setting()) {
			this -> setting = &setting;
			
			servoPos = setting.loadTempServoPos();
			maxPosition =  setting.data.maxRotateServoTemp;
			
			tempServo.setSpeed(50);   // ограничить скорость
			tempServo.setAccel(0.3);    // установить ускорение (разгон и торможение)
			
			tempServo.attach(tempServoPin, servoPos); //привязываем привод к порту
			tempServo.smoothStart();
		}
		
		void setServoPos(int position, bool isServiceMode = false) {
			if (!isServiceMode) {
				position = constrain(position, 0, 100);
				position = map(position, 0, 100, 0, maxPosition);
			}
			servoPos = position;
			setting -> saveTempServoPos(servoPos);
			
			printServoPos();
			
			tempServo.setTargetDeg(servoPos);	// max 180
		}
		
		void printServoPos() {
			int servoPosValue = map(servoPos, 0, maxPosition, 0, 100);
			
			Serial.print("temp_servo_pos=");
			Serial.println(servoPosValue);
		}
		
};
