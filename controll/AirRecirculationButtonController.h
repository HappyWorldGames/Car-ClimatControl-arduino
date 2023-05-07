#pragma once

class AirRecirculationButtonController {
	private:
		boolean isAirRecirculationEnabled = true;
		boolean isAirRecirculationActive = false;
		
		int mAirRecirculationReleyPin = -1;
		
	public:
		AirRecirculationButtonController(int airRecirculationReleyPin) {
			mAirRecirculationReleyPin = airRecirculationReleyPin;
			pinMode(airRecirculationReleyPin, OUTPUT);
		}
		
		void setAirRecirculationEnabled(boolean enabled){
			isAirRecirculationEnabled = enabled;
			if(!isAirRecirculationEnabled) setAirRecirculationActive(false);
		}
		
		void printAirRecirculationEnabled() {
			Serial.print("isAirRecirculationEnabled=");
			Serial.println(isAirRecirculationEnabled);
		}
		
		void setAirRecirculationActive(boolean active){
			isAirRecirculationActive = active;
			digitalWrite(mAirRecirculationReleyPin, isAirRecirculationActive && isAirRecirculationEnabled ? HIGH : LOW);
		}
		
		void printAirRecirculationActive() {
			Serial.print("isAirRecirculationActive=");
			Serial.println(isAirRecirculationActive);
		}
		
};