#pragma once

class FanController {
	private:
		int mTransistorPin = -1; // ПИН транзистора
		int mMinFanSpeed = -1; // Минимальные обороты
		int fanSpeed = -1; // скорость вентилятора
		
	public:
		FanController(int transistorPin, int minFanSpeed) {
			mTransistorPin = transistorPin;
			mMinFanSpeed = minFanSpeed;
		}
		
		void setFanSpeed(int speed, bool isServiceMode = false) {
			if (!isServiceMode) {
				if(speed != -1) {
					speed = constrain(speed, 0, 100);
					speed = map(speed, 0, 100, mMinFanSpeed, 255);
				}else speed = 0;
			}
			fanSpeed = speed;
			
			printFanSpeed();
			
			analogWrite(mTransistorPin, fanSpeed); //max 255
		}
		
		int getFanSpeed() {
			return fanSpeed;
		}
		
		void printFanSpeed(bool isServiceMode = false) {
			int fanSpeedValue = !isServiceMode ? map(fanSpeed, mMinFanSpeed, 255, 0, 100) : fanSpeed;
			
			Serial.print("fan_speed=");
			Serial.println(fanSpeedValue);
		}
		
};
