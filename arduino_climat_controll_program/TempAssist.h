#pragma once

// Other
#include <GyverPID.h>

class TempAssist {
	private:
		Setting* setting = NULL;
		
		GyverPID* servoTempPID = NULL;
		
		TemperatureSensor* tempSensor = NULL;
		
		FanController* fanController = NULL;
		TempServoController* tempServoController = NULL;
		
	public:
		TempAssist(Setting setting, TemperatureSensor tempSensor, FanController fanController, TempServoController tempServoController) {
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
			
			int tempInCar = tempSensor->getTemp(0);
			int tempInHeater = tempSensor->getTemp(1);
			int tempOutCar = tempSensor->getTemp(2);
			
			// Проверка ручного режима вентилятора
			if(!setting->data.manualFanSpeed) {
				if (setting->data.wantTempInCar > tempInCar && tempInHeater < setting->data.tempMinStartWork){
					if(fanController->getFanSpeed() > 0) fanController->setFanSpeed(-1);
				return;
				}
				//Максимальные обороты вентилятора
				int maxSpeedFan = setting->data.wantTempInCar < tempInCar ? 100 : map(tempInHeater, setting->data.tempMinStartWork, setting->data.tempMinStartWork + setting->data.tempMaxStartWork, 0, 100);
				maxSpeedFan = constrain(maxSpeedFan, 0, 100);
				
				//Разница температуры от заданной
				float diffTemp = abs(setting->data.wantTempInCar - tempInCar);
				
				//Вентилятор
				int localSpeedFan = map(diffTemp, 0, setting->data.diffSpeedFan, 0, maxSpeedFan);
				localSpeedFan = constrain(localSpeedFan, 0, maxSpeedFan);
				fanController->setFanSpeed(localSpeedFan);
			}
			
			// Проверка ручного режима заслонки тепло-холод
			if(!setting->data.manualServoTemp && servoTick >= setting->data.servoTickCount){
				servoTick = 0;
				if(abs(setting->data.wantTempInCar - tempInCar) > setting->data.deadRotateServoTemp){
					if (tempOutCar != 127.0) {
						// Формула
						int resFormula = ((setting->data.wantTempInCar - tempOutCar) * 100) / (tempInHeater - tempOutCar); // от 0 до 100 результат
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
		
		// Пока тут лежит
		void setManualFanSpeed(boolean manual){
			if(setting->data.manualFanSpeed == manual) return;
			setting->data.manualFanSpeed = manual;
			Serial.print("manualFanSpeed=");
			Serial.println(setting->data.manualFanSpeed);
		}
		void setManualServoHot(boolean manual){
			if(setting->data.manualServoTemp == manual) return;
			setting->data.manualServoTemp = manual;
			Serial.print("manualServoTemp=");
			Serial.println(setting->data.manualServoTemp);
		}
		
};