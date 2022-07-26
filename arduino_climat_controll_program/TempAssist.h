#pragma once

// Other
#include <GyverPID.h>

// My
#include "sensor/TemperatureSensor.h"

#include "controll/FanController.h"
#include "controll/TempServoController.h"

class TempAssist {
	private:
		Setting* setting = NULL;
		
		GyverPID* servoTempPID = NULL;
		
		TemperatureSensor* tempSensor = NULL;
		
		FanController* fanController = NULL;
		TempServoController* tempServoController = NULL;
		
	public:
		TempAssist(Setting& setting, TemperatureSensor& tempSensor, FanController& fanController, TempServoController& tempServoController) {
			this->setting = &setting;
			
			servoTempPID = &GyverPID(setting.data.servoHotPID[0], setting.data.servoHotPID[1], setting.data.servoHotPID[2]);
			servoTempPID->setDt(setting.data.AUTO_MODE_UPDATE_TIME * setting.data.servoTickCount);
			servoTempPID->setpoint = setting.data.wantTempInCar;
			servoTempPID->setLimits(0, setting.data.maxRotateServoTemp);
			servoTempPID->setDirection(REVERSE);
			
			this->tempSensor = &tempSensor;
			
			this->fanController = &fanController;
			this->tempServoController = &tempServoController;
		}
		
		void setWantTempInCar(int temp) {
			setting->data.wantTempInCar = temp;
		}
		
		void loop() {
			static uint32_t tmr;
			static byte servoTick = 0;
			if (millis() - tmr < setting->data.AUTO_MODE_UPDATE_TIME) return;
			tmr = millis();
			servoTick++;
			
			int tempInCar = tempSensor->getTemp(tempSensor->addressTempInCar);
			int tempInHeater = tempSensor->getTemp(tempSensor->addressTempInHeater);
			int tempOutCar = tempSensor->DEVICE_ERROR; //tempSensor->getTemp(2);
			
			tempSensor->printTemp(0);
			tempSensor->printTemp(1);
			tempSensor->printTemp(2);
			
			// Проверка ручного режима вентилятора
			if(!setting->data.manualFanSpeed) {
				if (setting->data.wantTempInCar > tempInCar && (tempInHeater < setting->data.tempMinStartWork && tempInHeater != tempSensor->DEVICE_ERROR)){
					if(fanController->getFanSpeed() > 0) fanController->setFanSpeed(-1);
					return;
				}
				//Максимальные обороты вентилятора
				int maxSpeedFan = setting->data.wantTempInCar < tempInCar ? 100 : map(tempInHeater, setting->data.tempMinStartWork, setting->data.tempMinStartWork + setting->data.tempMaxStartWork, 0, 100);
				maxSpeedFan = constrain(maxSpeedFan, 0, 100);
				
				//Разница температуры от заданной
				float diffTemp = abs(setting->data.wantTempInCar - tempInCar);
				
				//Вентилятор
				diffTemp = constrain(diffTemp, 0, setting->data.diffSpeedFan);
				int localSpeedFan = map(diffTemp, 0, setting->data.diffSpeedFan, 0, maxSpeedFan);
				localSpeedFan = constrain(localSpeedFan, 0, maxSpeedFan);
				fanController->setFanSpeed(localSpeedFan);
			}
			
			// Проверка ручного режима заслонки тепло-холод
			if(!setting->data.manualServoTemp && servoTick >= setting->data.servoTickCount){
				servoTick = 0;
				if(abs(setting->data.wantTempInCar - tempInCar) > setting->data.deadRotateServoTemp){
					if (tempOutCar != tempSensor->DEVICE_ERROR) {
						// Формула
						int resFormula = ((setting->data.wantTempInCar - tempOutCar) * 100) / (tempInHeater - tempOutCar); // от 0 до 100 результат
						// Если разница между заданной и в машине имеет разницу больше 6 градусов прибавить 10% в ту сторону куда нужно
						// abs(setting->data.wantTempInCar - tempInCar);
						resFormula = constrain(resFormula, 0, 100);
						
						tempServoController->setServoPos(resFormula);
					}else {
						//PID Регулятор
						servoTempPID->setDt(setting->data.AUTO_MODE_UPDATE_TIME * setting->data.servoTickCount);
						servoTempPID->input = tempInCar;
						servoTempPID->getResult();
						
						tempServoController->setServoPos(servoTempPID->output);
					}
				}
			}
			
			/* 
			*			Подключить кнопки через ардуино, после программно эмитировать, разные режимы:
			*				1) Нажатие кнопки разрешает использовать автоматике
			*				2) Нажатие кнопки передается напремую(ручно режим, как будто не было вмешательства)
			*				3) Нажатие кнопки включает принудительно, но при отжатии кнопки разрешает использовать автоматике
			*/
			//Управление рекупирацией и кондиционером
			/*if(digitalRead(BUTTON_AIR_RECIRCULATION_BUS) == HIGH) airRecirculation(true);
			else if(digitalRead(BUTTON_AIR_RECIRCULATION_BUS) == LOW && digitalRead(BUTTON_AIR_CONDITIONING_BUS) == LOW) airRecirculation(false);
			if(setting->tempSet < tempNowCar && tempNowOutCar > setting->tempSet && digitalRead(BUTTON_AIR_CONDITIONING_BUS) == HIGH && speedFan > 0){
				airConditioning(true);
				airRecirculation(true);
			}else airConditioning(false);*/
		  
		}
		
};