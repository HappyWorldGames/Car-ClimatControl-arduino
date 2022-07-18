/*
 * СОхранение и загрузка настроек здесь
 */

#include <EEPROM.h>

class Setting {
  private:
	
  public:
    struct {
      #define TRANSISTOR_PIN 3                        // TRANSISTOR
      #define ONE_WIRE_PIN 4                          // DS18B20 - датчики температуры
      #define RELAY_AIR_RECIRCULATION_PIN 6           // Реле рециркуляции воздуха
      #define RELAY_AIR_CONDITIONING_PIN 7            // Реле кондиционера
      #define RELAY_SERVO_SIGNAL_PIN 8                // Реле
      #define SERVO_PIN 9                             // Серво-Мотор
      #define BUTTON_AIR_RECIRCULATION_PIN 10         // Кнопка рециркуляции
      #define BUTTON_AIR_CONDITIONING_PIN 11          // Кнопка кондиционера
                                      //Аналоговые
      #define HEATER_TEMP_PIN A0                      // A0 = Температура в печке
    } pin;
    
    struct {
      int AUTO_MODE_UPDATE_TIME = 2000; // время обновления авто-режима
      
      int tempMinStartWork = 40; // минимальная температура при которой начнётся нагрев салона
      int tempMaxStartWork = 20; // tempMinStartWork + tempMaxStartWork = когда вентелятор будет дуть на полную
      int diffSpeedFan = 6; // от 0 до diffSpeedFan, интерпритируются от minSpeedFan до 255, разница скорости вентилятора от заданной температуры
      
      float wantTempInCar = 22.0; // установление значения желаемой температуры
      
      boolean alwaysOnFan = true;
      int minSpeedFan = 120;
      
      int maxRotateServoHot = 180;
      float deadRotateServoHot = 1; // разница температуры от заданной при которой не будет работать заслонка тепло-холод
      
      boolean manualFanSpeed = false;
      boolean manualServoHot = false;
    } data;
  
    Setting() {}

    void printSetting() {
		Serial.println("AUTO_MODE_UPDATE_TIME=" + data.AUTO_MODE_UPDATE_TIME);
		
		Serial.println("tempMinStartWork=" + data.tempMinStartWork);
		Serial.println("tempMaxStartWork=" + data.tempMaxStartWork);
    }

    void saveTempServoPos(int pos) {
      EEPROM.update(1, (byte)pos);
	  Serial.println("Saved Servo Pos");
      // Зарезервированна ячейка 1 EEPROM, буду сохранять от 0 до 100
    }
    int loadTempServoPos() {
      return (int)EEPROM[1];
	  Serial.println("Loaded Servo Pos");
    }
    
    void save() {
      EEPROM.update(0, 0); // Записываем в первую ячейку 0, потому что по умолчанию там 255 (Даем знать что есть сохранения)
      EEPROM.put(2, data); // Записываем настройки
      Serial.println("Saved");
    }
    void load() {
      if(EEPROM[0] == 255) return; // Проверяем первую ячейку памяти, если она равна 255, то нечего не делаем
      EEPROM.get(2, data); // Если не равна 255, то читаем настройки
      
      Serial.println("Loaded");
    }
    void resetSave(){
      EEPROM.update(0, 255); // Записываем в первую ячейку 255, обнуляя ячейку
      Serial.println("Save reset");
    }
};