#include <GyverPID.h>

#include "sensor/TemperatureSensor.h"
#include "Setting.h"

class TempAssist {
  private:
    Setting setting();
    TemperatureSensor tempSensor(PIN);

    GyverPID servoHotPID(14, 0.82, 0); //15.2 0.82 0
  public:
    TempAssist() {
      
    }

    void setWantTempInCar(int temp) {
      this->wantTempInCar = temp;
    }

    void loop() {
      int tempInCar = tempSensor.getTemp(0);
      int tempInHeater = tempSensor.getTemp(1);
      int tempOutCar = tempSensor.getTemp(2);

      // Проверка ручного режима вентилятора
      if(!setting.manualFanSpeed) {
        if (setting.tempSet > tempNowCar && tempNowHeater < setting.tempMinStartWork){
          if(speedFan > 0) setSpeedFan(-1);
          return;
        }
        //Максимальные обороты вентилятора
        int maxSpeedFan = setting.tempSet < tempNowCar ? 100 : map(tempNowHeater, setting.tempMinStartWork, setting.tempMinStartWork + setting.tempMaxStartWork, 0, 100);
        maxSpeedFan = constrain(maxSpeedFan, 0, 100);
        
        //Разница температуры от заданной
        float diffTemp = abs(setting.tempSet - tempNowCar);
      
        //Вентилятор
        int localSpeedFan = map(diffTemp, 0, setting.diffSpeedFan, 0, maxSpeedFan);
        localSpeedFan = constrain(localSpeedFan, 0, maxSpeedFan);
        setSpeedFan(localSpeedFan);
      }
    }
}
