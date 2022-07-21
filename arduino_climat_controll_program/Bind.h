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
		
		/*
		*	Service command:
		* 		// 1** - связан с вентилятором
		*		11 ** = тест скорости вентилятора (абсолютный)
		*		12 ** = тест скорости вентилятора (относительный)(с учетом минимума)
		*		13 *(0 или 1) = всегда включен вентилятор
		*		14 *** = установка минимальной скорости вентилятора(max 255)
		*
		*		// 2** - связан с серво-мотором, тепло-холод
		*		21 ** = тест положения тепло-холод (абсолютный)
		*		22 ** = тест положения тепло-холод (относительный)(с учетом ограничений)
		*		24 *** = установка максимального положения тепло-холод
		*		25 ** = установить метвую зону в градусах сервопривода
		*
		*		// 3** - связан с серво-мотором, направление потока воздуха
		*		31 ** = тест положения направление потока воздуха (абсолютный)
		*		32 ** = тест положения направление потока воздуха (относительный)(с учетом ограничений)
		*		33 ** = тест положения направление потока воздуха в мкс
		*		34 *** = установка максимального положения направление потока воздуха
		*
		*		// 4** - связан с датчиками температуры
		*		41 = тест датчика температуры(запрос температуры)
		*		42 ** = установить минимальную начальную температуру
		*		43 ** = установить максимальную начальную температуру
		*		44 ** = установить разницу скорости вентилятора от заданой температуры
		*		45 ** = установить температуру в печке
		*		46 ** = установить температуру в машине
		*		47 ** = установить температуру вне машины
		*
		*		// 5** - прочее
		*		51 ** = время обновления авто режима
		*		52 * * * * = изменнить PID (0 = servoHotPID; 1 = fanSpeedPID) значение P I D
		*		53 * = показать PID (0 = servoHotPID; 1 = fanSpeedPID)
		*		54 * = изменить servoTickCount(max 255)
		*		55 * = изменить fanSpeedType(max 255)(0 = PID, 1 = Linear)
		*/
		void onService(int cmd) {
			switch (cmd) {
				//вентилятор
				case 11:
					fanController->setFanSpeed(Serial.parseInt(), true);
					break;
				case 12:
					fanController->setFanSpeed(Serial.parseInt());
					break;
				case 13:
					setting->data.alwaysOnFan = Serial.parseInt();
					fanController->setFanSpeed(fanController->getFanSpeed());
					setting->printSetting();
				  break;
				case 14:
					setting->data.minSpeedFan = Serial.parseInt();
					setting->printSetting();
				  break;
				//тепло-холод
				case 21:
					tempServoController->setServoPos(Serial.parseInt(), true);
					break;
				case 22:
					tempServoController->setServoPos(Serial.parseInt());
					break;
				case 24:
					setting->data.maxRotateServoTemp = Serial.parseInt();
					setting->printSetting();
					break;
				/*case 25:
				  setting.deadRotateServoHot = Serial.parseFloat();
				  Serial.print("deadRotateServoHot ");
				  Serial.println(setting.deadRotateServoHot);
				  break;
				//направление потока воздуха
				case 31:
				  setRotateServoAirWay(Serial.parseInt(), true);
				  break;
				case 32:
				  setRotateServoAirWay(map(Serial.parseInt(), 0, 100, 0, setting.maxRotateServoHot));
				  break;
				case 33:
				  servoHot.setTarget(Serial.parseInt());
				  Serial.print("write_servo_micro ");
				  Serial.println(servoHot.getTarget());
				  break;
				//Температура
				case 41:
				  getTemp();
				  break;
				case 42:
				  setting.tempMinStartWork = Serial.parseInt();
				  Serial.print("tempMinStartWork ");
				  Serial.println(setting.tempMinStartWork);
				  break;
				case 43:
				  setting.tempMaxStartWork = Serial.parseInt();
				  Serial.print("tempMaxStartWork ");
				  Serial.println(setting.tempMaxStartWork);
				  break;
				case 44:
				  setting.diffSpeedFan = Serial.parseInt();
				  Serial.print("diffSpeedFan ");
				  Serial.println(setting.diffSpeedFan);
				  break;
				case 45:
				  tempNowHeater = Serial.parseFloat();
				  Serial.print("tempNowHeater ");
				  Serial.println(tempNowHeater);
				  break;
				case 46:
				  tempNowCar = Serial.parseFloat();
				  Serial.print("tempNowCar ");
				  Serial.println(tempNowCar);
				  break;
				case 47:
				  tempNowOutCar = Serial.parseFloat();
				  Serial.print("tempNowOutCar ");
				  Serial.println(tempNowOutCar);
				  break;
				//Прочее
				case 51:
				  setting.AUTO_MODE_UPDATE_TIME = Serial.parseInt();
				  servoHotPID.setDt(setting.AUTO_MODE_UPDATE_TIME * setting.servoTickCount);
				  fanSpeedPID.setDt(setting.AUTO_MODE_UPDATE_TIME);
				  Serial.print("AUTO_MODE_UPDATE_TIME ");
				  Serial.println(setting.AUTO_MODE_UPDATE_TIME);
				  break;
				case 52:
				  switch(Serial.parseInt()){
					case 0:
					  setting.servoHotPID[0] = Serial.parseFloat();
					  setting.servoHotPID[1] = Serial.parseFloat();
					  setting.servoHotPID[2] = Serial.parseFloat();
					  showServoHotPID();
					  break;
					case 1:
					  setting.fanSpeedPID[0] = Serial.parseFloat();
					  setting.fanSpeedPID[1] = Serial.parseFloat();
					  setting.fanSpeedPID[2] = Serial.parseFloat();
					  showFanSpeedPID();
					  break;
				  }
				  updatePID();
				  break;
				case 53:
				  switch(Serial.parseInt()){
					case 0:
					  showServoHotPID();
					  break;
					case 1:
					  showFanSpeedPID();
					  break;
				  }
				  break;
				case 54:
				  setting.servoTickCount = Serial.parseInt();
				  Serial.print("servoTickCount ");
				  Serial.println(setting.servoTickCount);
				  break;
				case 55:
				  setting.fanSpeedType = Serial.parseInt();
				  Serial.print("fanSpeedType ");
				  Serial.println(setting.fanSpeedType);
				  break;
				default:
				  Serial.print("command '");
				  Serial.print(command);
				  Serial.println("' not found");
				  break;*/
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
