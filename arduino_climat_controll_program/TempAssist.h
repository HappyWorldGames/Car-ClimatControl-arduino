// Other
#include <GyverPID.h>

// My
#include "sensor/TemperatureSensor.h"
#include "Setting.h"

#include "controll/FanController.h"

class TempAssist {
  private:
	Setting setting = Setting();
    
	//GyverPID servoHotPID(14f, 0.82f, 0.0f, setting.data.AUTO_MODE_UPDATE_TIME); //15.2 0.82 0
	
	TemperatureSensor tempSensor = TemperatureSensor(setting.pin.ONE_WIRE_PIN);
	FanController fanController = FanController(setting.pin.TRANSISTOR_PIN, setting.data.minSpeedFan);
	
  public:
    TempAssist() {}

    void setWantTempInCar(int temp) {
      setting.data.wantTempInCar = temp;
    }

    void loop() {
      int tempInCar = tempSensor.getTemp(0);
      int tempInHeater = tempSensor.getTemp(1);
      int tempOutCar = tempSensor.getTemp(2);

      // Проверка ручного режима вентилятора
      if(!setting.data.manualFanSpeed) {
        if (setting.data.wantTempInCar > tempInCar && tempInHeater < setting.data.tempMinStartWork){
          if(fanController.getFanSpeed() > 0) fanController.setFanSpeed(-1);
          return;
        }
        //Максимальные обороты вентилятора
        int maxSpeedFan = setting.data.wantTempInCar < tempInCar ? 100 : map(tempInHeater, setting.data.tempMinStartWork, setting.data.tempMinStartWork + setting.data.tempMaxStartWork, 0, 100);
        maxSpeedFan = constrain(maxSpeedFan, 0, 100);
        
        //Разница температуры от заданной
        float diffTemp = abs(setting.data.wantTempInCar - tempInCar);
      
        //Вентилятор
        int localSpeedFan = map(diffTemp, 0, setting.data.diffSpeedFan, 0, maxSpeedFan);
        localSpeedFan = constrain(localSpeedFan, 0, maxSpeedFan);
        fanController.setFanSpeed(localSpeedFan);
      }
    }
};