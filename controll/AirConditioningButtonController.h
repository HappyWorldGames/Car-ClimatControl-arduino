#pragma once

class AirConditioningButtonController {
	private:
		boolean isAirConditioningEnabled = true;
		boolean isAirConditioningActive = false;
		
		int mAirConditioningReleyPin = -1;
		
	public:
		AirConditioningButtonController(int airConditioningReleyPin) {
			mAirConditioningReleyPin = airConditioningReleyPin;
			pinMode(airConditioningReleyPin, OUTPUT);
		}
		
		void setAirConditioningEnabled(boolean enabled){
			isAirConditioningEnabled = enabled;
			if(!isAirConditioningEnabled) setAirConditioningActive(false);
		}
		
		void printAirConditioningEnabled() {
			Serial.print("isAirConditioningEnabled=");
			Serial.println(isAirConditioningEnabled);
		}
		
		void setAirConditioningActive(boolean active){
			isAirConditioningActive = active;
			digitalWrite(mAirConditioningReleyPin, isAirConditioningActive && isAirConditioningEnabled ? HIGH : LOW);
		}
		
		void printAirConditioningActive() {
			Serial.print("isAirConditioningActive=");
			Serial.println(isAirConditioningActive);
		}
		
};
