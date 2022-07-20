// Other


// My
#include "Setting.h"
#include "Bind.h"

#include "sensor/TemperatureSensor.h"

#include "controll/FanController.h"
#include "controll/TempServoController.h"

/*
#include "controll/AirRecirculationButtonController.h"
#include "controll/AirConditioningButtonController.h"
#include "OBD2.h"

AirRecirculationButtonController airRecirculationButtonController();
AirConditioningButtonController airConditioningButtonController();
*/
#include "TempAssist.h"

/*
	Command List:
		403 = запрос версии прошивки
		404 = сохранение
	405 = сброс сохранений
  908 = сигнализирует о подключение устройства(нужно сообщить все показатели)
  909 = автоматический режим {
    01 ** = устанавливает желаемую температуру
    11 *** = установка скорости вентилятора(0-100)
    12 *(0 или 1) = всегда включен вентилятор
    13 = выключить ручной режим для вентилятора
    22 *** = установка положения тепло-холод(0-100), где 50 середина
    23 = выключить ручной режим для заслонки тепло-холод
  }
  910 = ручной режим {
    11 *** = установка скорости вентилятора(0-100)
    12 *(0 или 1) = всегда включен вентилятор
    22 *** = установка положения тепло-холод(0-100), где 50 середина
  }
  911 = сервисный режим {
    // 1** - связан с вентилятором
    11 ** = тест скорости вентилятора (абсолютный)
    12 ** = тест скорости вентилятора (относительный)(с учетом минимума)
    13 *(0 или 1) = всегда включен вентилятор
    14 *** = установка минимальной скорости вентилятора(max 255)

    // 2** - связан с серво-мотором, тепло-холод
    21 ** = тест положения тепло-холод (абсолютный)
    22 ** = тест положения тепло-холод (относительный)(с учетом ограничений)
    23 ** = тест положения тепло-холод в мкс
    24 *** = установка максимального положения тепло-холод
    25 ** = установить метвую зону в градусах сервопривода

    // 3** - связан с серво-мотором, направление потока воздуха
    31 ** = тест положения направление потока воздуха (абсолютный)
    32 ** = тест положения направление потока воздуха (относительный)(с учетом ограничений)
    33 ** = тест положения направление потока воздуха в мкс
    34 *** = установка максимального положения направление потока воздуха

    // 4** - связан с датчиками температуры
    41 = тест датчика температуры(запрос температуры)
    42 ** = установить минимальную начальную температуру
    43 ** = установить максимальную начальную температуру
    44 ** = установить разницу скорости вентилятора от заданой температуры
    45 ** = установить температуру в печке
    46 ** = установить температуру в машине
    47 ** = установить температуру вне машины

    // 5** - прочее
    51 ** = время обновления авто режима
    52 * * * * = изменнить PID (0 = servoHotPID; 1 = fanSpeedPID) значение P I D
    53 * = показать PID (0 = servoHotPID; 1 = fanSpeedPID)
    54 * = изменить servoTickCount(max 255)
    55 * = изменить fanSpeedType(max 255)(0 = PID, 1 = Linear)
  }
*/

#define VERSION "2022.07.20" // Date format yyyy.mm.dd

boolean initEnd = false; 					//Чтобы не дерггать сервомотор в начале

Setting setting = Setting();

TemperatureSensor tempSensor = TemperatureSensor(setting.pin.ONE_WIRE_PIN);
		
FanController fanController = FanController(setting.pin.TRANSISTOR_PIN, setting.data.minSpeedFan);
TempServoController tempServoController = TempServoController(setting.pin.TEMP_SERVO_PIN, setting);

TempAssist tempAssist = TempAssist(setting, tempSensor, fanController, tempServoController);

void setup() {
  TCCR2B = 0b00000001; // x1
  TCCR2A = 0b00000011; // fast pwm
/*
  pinMode(RELAY_SERVO_SIGNAL_BUS, OUTPUT);
  digitalWrite(RELAY_SERVO_SIGNAL_BUS, LOW);

  Serial.begin(9600);
  initControllButton();
  initSensorTemperature();
  initControllServo();
*/
}

void loop() {
  /*
  if (Serial.available()) {
    int command = Serial.parseInt();
    switch (command) {
      case 403:
        getVersion();
        break;
      case 404:
        save();
        break;
      case 405:
        resetSave();
        break;
      case 908:
        getStatus();
        break;
      case 909: mode = 0;
        Serial.println("Auto_Mode");
        break;
      case 910: mode = 1;
        Serial.println("Manual_Mode");
        break;
      case 911: mode = 2;
        Serial.println("Service_Mode");
        break;
      default: switch (mode) {
          case 0:
            serialAutoMode(command);
            break;
          case 1:
            serialManualMode(command);
            break;
          case 2:
            serialServiceMode(command);
            break;
        }
        break;
    }
  }
  switch (mode) {
    case 0:
      autoMode();
      break;
    case 1:
      manualMode();
      break;
    case 2:
      serviceMode();
      break;
  }

  servoHot.tick();

  //Чтобы не дергать серво-мотор тепло-холод при включении
  if(!initEnd){
    static uint32_t ztmr;
    if (millis() - ztmr < 4000) return;
    ztmr = millis();
    digitalWrite(RELAY_SERVO_SIGNAL_BUS, HIGH);

    rotateServoHot = -1;
    
    initEnd = true;
  }*/
}

void getStatus(){
	printVersion();
	
	setting.printSetting();
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

void printVersion(){
	Serial.print("VERSION=");
	Serial.println(VERSION);
}