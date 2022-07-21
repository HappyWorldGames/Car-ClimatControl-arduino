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


boolean initEnd = false; 					//Чтобы не дерггать сервомотор в начале

Setting setting = Setting();

TemperatureSensor tempSensor = TemperatureSensor(setting.pin.ONE_WIRE_PIN);
		
FanController fanController = FanController(setting.pin.TRANSISTOR_PIN, setting.data.minSpeedFan, setting.data.alwaysOnFan);
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
