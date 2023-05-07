#pragma once

class FanController {
	private:
		int mTransistorPin = -1; 			// ПИН транзистора
		int mMinFanSpeed = -1; 				// Минимальные обороты
		boolean mAlwaysOnFan = false;		// Крутиться при 0
		
		int fanSpeed = -1; 					// скорость вентилятора
		
	public:
		FanController(int transistorPin, int minFanSpeed, boolean alwaysOnFan) {
			mTransistorPin = transistorPin;
			mMinFanSpeed = minFanSpeed;
			mAlwaysOnFan = alwaysOnFan;
		}
		
		void setFanSpeed(int speed, bool isServiceMode = false) {
			if (!isServiceMode) {
				if(!mAlwaysOnFan && speed == 0 || speed < 0){
					speed = 0;
				} else {
					speed = constrain(speed, 0, 100);
					speed = map(speed, 0, 100, mMinFanSpeed, 255);
				}
			}
			fanSpeed = speed;
			
			printFanSpeed(isServiceMode);
			
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
