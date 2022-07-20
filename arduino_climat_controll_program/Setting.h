/*
 * СОхранение и загрузка настроек здесь
 */
#pragma once

#include <EEPROM.h>

class Setting {
	private:
		
	public:
		struct {
			const int TRANSISTOR_PIN = 3;                        	// TRANSISTOR
			const int ONE_WIRE_PIN = 4;                          	// DS18B20 - датчики температуры
			const int RELAY_AIR_RECIRCULATION_PIN = 6;           	// Реле рециркуляции воздуха
			const int RELAY_AIR_CONDITIONING_PIN = 7;            	// Реле кондиционера
			const int RELAY_SERVO_SIGNAL_PIN = 8;                	// Реле
			const int TEMP_SERVO_PIN = 9;                      		// Серво-Мотор
			const int BUTTON_AIR_RECIRCULATION_PIN = 10;         	// Кнопка рециркуляции
			const int BUTTON_AIR_CONDITIONING_PIN = 11;          	// Кнопка кондиционера
												//Аналоговые
			const int HEATER_TEMP_PIN = A0;                      	// A0 = Температура в печке
		} pin;
		
		struct {
			byte mode = 0;									// Режим работы (0 - серсисный, 1 - нормальный)
			
			int AUTO_MODE_UPDATE_TIME = 2000; 				// время обновления авто-режима
			
			int tempMinStartWork = 40; 						// минимальная температура при которой начнётся нагрев салона
			int tempMaxStartWork = 20; 						// tempMinStartWork + tempMaxStartWork = когда вентелятор будет дуть на полную
			int diffSpeedFan = 6; 							// от 0 до diffSpeedFan, интерпритируются от minSpeedFan до 255, разница скорости вентилятора от заданной температуры
			
			float wantTempInCar = 22.0; 					// установление значения желаемой температуры
			
			boolean alwaysOnFan = true;
			int minSpeedFan = 120;
			
			int maxRotateServoTemp = 180;
			float deadRotateServoTemp = 1; 					// разница температуры от заданной при которой не будет работать заслонка тепло-холод
			float servoHotPID[3] = { 14, 0.82, 0 };			// old value (15.2, 0,.82 0)
			byte servoTickCount = 5;
			
			boolean manualFanSpeed = false;
			boolean manualServoTemp = false;
		} data;
	  
		Setting() {
			load();
		}
		
		void printSetting() {
			Serial.println("mode=" + data.mode);
			
			Serial.println("AUTO_MODE_UPDATE_TIME=" + data.AUTO_MODE_UPDATE_TIME);
			
			Serial.println("tempMinStartWork=" + data.tempMinStartWork);
			Serial.println("tempMaxStartWork=" + data.tempMaxStartWork);
			Serial.println("diffSpeedFan=" + data.diffSpeedFan);
			
			Serial.println("wantTempInCar=" + String(data.wantTempInCar, 2));
			
			Serial.println("alwaysOnFan=" + data.alwaysOnFan);
			Serial.println("minSpeedFan=" + data.minSpeedFan);
			
			Serial.println("maxRotateServoTemp=" + data.maxRotateServoTemp);
			Serial.println("deadRotateServoTemp=" + String(data.deadRotateServoTemp, 2));
			Serial.println("servoHotPID=" + String(data.servoHotPID[0], 2) + ' ' + String(data.servoHotPID[1], 2) + ' ' + String(data.servoHotPID[2], 2));
			Serial.println("servoTickCount=" + data.servoTickCount);
			
			Serial.println("manualFanSpeed=" + data.manualFanSpeed);
			Serial.println("manualServoTemp=" + data.manualServoTemp);
		}
		
		void saveTempServoPos(int pos) {
			// Зарезервированна ячейка 1 EEPROM, буду сохранять от 0 до 100
			EEPROM.update(1, (byte)pos);
			Serial.println("Saved Servo Pos");
		}
		int loadTempServoPos() {
			Serial.println("Loaded Servo Pos");
			return (int)EEPROM[1];
		}
		
		void save() {
			EEPROM.update(0, 0); 						// Записываем в первую ячейку 0, потому что по умолчанию там 255 (Даем знать что есть сохранения)
			EEPROM.put(2, data); 						// Записываем настройки
			Serial.println("Saved");
		}
		void load() {
			if(EEPROM[0] == 255) return; 					// Проверяем первую ячейку памяти, если она равна 255, то нечего не делаем
			EEPROM.get(2, data); 							// Если не равна 255, то читаем настройки
			
			Serial.println("Loaded");
		}
		void resetSave(){
			EEPROM.update(0, 255); 						// Записываем в первую ячейку 255, обнуляя ячейку
			Serial.println("Save reset");
		}
		
};
