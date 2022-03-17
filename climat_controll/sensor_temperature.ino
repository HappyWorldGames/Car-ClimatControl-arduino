//Temperature Address
//Long address 28AA19C85214019A
//Short address 28BC6794970203EA

#define R1 220
#define vin 5

void initSensorTemperature(){
  sensor.begin(); // инициализация DS18B20
  // установка точности измерения 9...12 разрядов
  sensor.setResolution(addressTempInHeater, TEMPERATURE_PRECISION);
  sensor.setResolution(addressTempInCar, TEMPERATURE_PRECISION);
}

void setTemp(float temp) {
  if (temp < 5 || temp > 40 || temp == setting.tempSet) return;
  setting.tempSet = temp;

  servoHotPID.setpoint = setting.tempSet;
  fanSpeedPID.setpoint = setting.tempSet;

  Serial.print("Temp_Set: ");
  Serial.println(setting.tempSet);
}
void getTemp() {
  sensor.requestTemperatures(); // считывание значение температуры

  //считывание температуры в печке
  Serial.print("Heater ");
  float tempTemp = sensor.getTempC(addressTempInHeater); // температура в градусах Цельсия
  if (tempTemp > -50 && tempTemp < 120) tempNowHeater = tempTemp;
  Serial.print(tempNowHeater);
  Serial.println("°C");
  /*Serial.print("Heater ");
  int sensorValue=analogRead(HEATER_TEMP_BUS);
  float voltage=sensorValue*(5.0/1023.0);
  float tempTemp = tempFromResistance(resistance(voltage)); // температура в градусах Цельсия
  if (tempTemp > -50 && tempTemp < 120) tempNowHeater = tempTemp;
  Serial.print(tempNowHeater);
  Serial.println("°C");*/

  //считывание температуры в машине
  //printAddress(addressTempInCar);
  Serial.print("Car ");
  tempTemp = sensor.getTempC(addressTempInCar); // температура в градусах Цельсия
  if (tempTemp > -50 && tempTemp < 50) tempNowCar = tempTemp;
  Serial.print(tempNowCar);
  Serial.println("°C");

  //считывание температуры вне машины
  //printAddress(addressTempInHeater);
  /*Serial.print("OutCar ");
  tempTemp = sensor.getTempC(addressTempInHeater); // температура в градусах Цельсия
  if (tempTemp > -50 && tempTemp < 50) tempNowOutCar = tempTemp;
  Serial.print(tempNowOutCar);
  Serial.println("°C");*/
}
/*void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16)
      Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
  Serial.print(" ");
}*/
float resistance(float vout){
  return R1*(1/(vin/vout-1));
}
float tempFromResistance(float resistance){
  if(resistance >= 80 && resistance <= 120) return 0.0004*(resistance*resistance)-0.3710*resistance+157.3873;
  else if(resistance >= 25 && resistance < 80) return 0.0*(resistance*resistance)-0.0706*resistance+104.5140;
  else if(resistance >= 0 && resistance < 25) return 0.0*(resistance*resistance)-0.0100*resistance+50.6413;
  else if(resistance >= -20 && resistance < 0) return 0.0*(resistance*resistance)-0.0023*resistance+19.7622;
  return -0.0*(resistance*resistance*resistance)+0.0*(resistance*resistance)-0.0315*resistance+102.2468;
}
