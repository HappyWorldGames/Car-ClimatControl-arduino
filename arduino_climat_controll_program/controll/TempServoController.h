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
			if(maxPosition == 255) maxPosition = 180;
			if(servoPos > maxPosition) servoPos = 0;
			
			tempServo.setSpeed(50);   // ограничить скорость
			tempServo.setAccel(0.3);    // установить ускорение (разгон и торможение)
			
			tempServo.write(servoPos);
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
			
			printServoPos(isServiceMode);
			
			tempServo.setTargetDeg(servoPos);	// max 180
		}
		
		void printServoPos(bool isServiceMode = false) {
			int servoPosValue = !isServiceMode ? map(servoPos, 0, maxPosition, 0, 100) : servoPos;
			
			Serial.print("temp_servo_pos=");
			Serial.println(servoPosValue);
		}
		
		void tick() {
			tempServo.tick();
		}
		
};
