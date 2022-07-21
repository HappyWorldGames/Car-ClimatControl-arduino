#pragma once

#include "sensor/TemperatureSensor.h"

#include "controll/FanController.h"
#include "controll/TempServoController.h"

class Bind {
	private:
		Setting *setting = NULL;
		
		TemperatureSensor* tempSensor = NULL;
		
		FanController* fanController = NULL;
		TempServoController* tempServoController = NULL;
		
		int nextInt() {
			return Serial.parseInt();
		}
		
		/*
		*	Normal command:
		*		01 ** = устанавливает желаемую температуру
		*		11 *** = установка скорости вентилятора(0-100)
		*		13 = выключить ручной режим для вентилятора
		*		22 *** = установка положения тепло-холод(0-100), где 50 середина
		*		23 = выключить ручной режим для заслонки тепло-холод
		*/
		void onNormal(int cmd) {
			switch (cmd) {
				case 01:
					setting->setWantTempInCar(Serial.parseFloat());
					break;
				case 11:
					setting->setManualFanSpeed(true);
					fanController->setFanSpeed(Serial.parseInt());
					break;
				case 13:
					setting->setManualFanSpeed(false);
					break;
				case 22:
					setting->setManualServoTemp(true);
					tempServoController->setServoPos(Serial.parseInt());
					break;
				case 23:
					setting->setManualServoTemp(false);
					break;
			}
		}
		
		void onService(int cmd) {
			switch(cmd) {
				
			}
		}
		
		void printStatus(){
			setting->printSetting();
			/*
			getStatusControllFan();
			getStatusControllServo();
			getTemp();
			getStatusControllButton();
			
			switch(mode){
				case 1:
					printStatusModeAuto();
					break;
				case 0:
					getStatusModeService();
					break;
			}*/
		}
		
	public:
		
		Bind(Setting setting, TemperatureSensor tempSensor, FanController fanController, TempServoController tempServoController) {
			this->setting = &setting;
			
			this->tempSensor = &tempSensor;
			
			this->fanController = &fanController;
			this->tempServoController = &tempServoController;
		}
		
		/*
		*	system command:
		*		403 = запрос версии прошивки
		*		404 = сохранение
		*		405 = сброс сохранений
		*		908 = сигнализирует о подключение устройства(нужно сообщить все показатели)
		*		909 = normal mode
		*		911 = service mode
		*/
		bool waitCommand() {
			if(!Serial.available()) return false;
			int cmd = nextInt();
			switch(cmd) {
				case 403:
					setting->printVersion();
					break;
				case 404:
					setting->save();
					break;
				case 405:
					setting->resetSave();
					break;
				case 908:
					printStatus();
					break;
				case 909:
					setting->setMode(1);
					break;
				case 911:
					setting->setMode(0);
					break;
				default:
					switch(setting->data.mode) {
						case 1:
							onNormal(cmd);
							break;
						case 0:
							onService(cmd);
							break;
					}
					break;
			}
			return true;
		}
};
