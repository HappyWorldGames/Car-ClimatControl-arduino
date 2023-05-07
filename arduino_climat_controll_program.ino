// Other


// My
#include "Setting.h"
#include "Bind.h"

#include "sensor/TemperatureSensor.h"

#include "controll/FanController.h"
#include "controll/TempServoController.h"

#include "TempAssist.h"
#include "ServiceAssist.h"

/*
#include "controll/AirRecirculationButtonController.h"
#include "controll/AirConditioningButtonController.h"
#include "OBD2.h"

AirRecirculationButtonController airRecirculationButtonController();
AirConditioningButtonController airConditioningButtonController();
*/

boolean initEnd = false; 					// Чтобы не дерггать сервомотор в начале

Setting setting = Setting();				// Настройки

TemperatureSensor tempSensor = TemperatureSensor(setting.pin.ONE_WIRE_PIN);														// Класс для получения температуры

FanController fanController = FanController(setting.pin.TRANSISTOR_PIN, setting.data.minSpeedFan, setting.data.alwaysOnFan);	// Класс для управления вентилятором
TempServoController tempServoController = TempServoController(setting.pin.TEMP_SERVO_PIN, setting);								// Класс для управления заслонкой тепло-холод

Bind bind = Bind(setting, tempSensor, fanController, tempServoController);							// Класс для обработки комманд
TempAssist tempAssist = TempAssist(setting, tempSensor, fanController, tempServoController);		// Класс для автоматики
ServiceAssist serviceAssist = ServiceAssist();														// Класс для сервисного режима

void setup() {
	TCCR2B = 0b00000001; // x1
	TCCR2A = 0b00000011; // fast pwm

	pinMode(setting.pin.RELAY_SERVO_SIGNAL_PIN, OUTPUT);
	digitalWrite(setting.pin.RELAY_SERVO_SIGNAL_PIN, setting.data.detechServo ? LOW : HIGH);

	Serial.begin(9600);
	Serial.println("Start");
	//initControllButton();
}

void loop() {
	bind.waitCommand();
	
	switch (setting.data.mode) {
		case 0:
			serviceAssist.loop();
			break;
		case 1:
			tempAssist.loop();
			break;
	}
	
	tempServoController.tick();

	//Чтобы не дергать серво-мотор тепло-холод при включении
	if(setting.data.detechServo && !initEnd){
		static uint32_t ztmr;
		if (millis() - ztmr < 4000) return;
		ztmr = millis();
		digitalWrite(setting.pin.RELAY_SERVO_SIGNAL_PIN, HIGH);
		
		//rotateServoHot = -1;
		
		initEnd = true;
	}
}
