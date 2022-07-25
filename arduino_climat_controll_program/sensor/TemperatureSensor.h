#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>

//Temperature Address
//Long address 28AA19C85214019A
//Short address 28BC6794970203EA

class TemperatureSensor {
	private:
		#define TEMPERATURE_PRECISION 11 // точность измерений (9 ... 12)
		
		OneWire oneWire; //Говорим к какому пину подключены датчики температуры
		DallasTemperature sensor;
		
	public:
		const int DEVICE_ERROR = -127;
		
		DeviceAddress addressTempInHeater = { 0x28, 0xBC, 0x67, 0x94, 0x97, 0x02, 0x03, 0xEA };
		DeviceAddress addressTempInCar = { 0x28, 0xAA, 0x19, 0xC8, 0x52, 0x14, 0x01, 0x9A} ;
		DeviceAddress addressTempOutCar = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		
		TemperatureSensor(int oneWirePin) {
			oneWire = OneWire(oneWirePin);
			sensor = DallasTemperature(&oneWire);
			
			sensor.begin(); // инициализация DS18B20
			// установка точности измерения 9...12 разрядов
			sensor.setResolution(addressTempInHeater, TEMPERATURE_PRECISION);
			sensor.setResolution(addressTempInCar, TEMPERATURE_PRECISION);
		}
		
		/*
		 * tempId
		 * 0 = Салон
		 * 1 = Печка
		 * 2 = Улица
		 */
		void printTemp(int tempId) {
			sensor.requestTemperatures(); // считывание значение температуры
			switch(tempId) {
				case 0:
					Serial.print("incar=");
					Serial.println(getTemp(addressTempInCar));
					break;
				case 1:
					Serial.print("heater=");
					Serial.println(getTemp(addressTempInHeater));
					break;
				case 2:
					Serial.print("outcar=");
					Serial.println(getTemp(addressTempOutCar));
					break;
			}
		}
		
		float getTemp(DeviceAddress deviceId) {
			float tempTemp = sensor.getTempC(deviceId); // температура в градусах Цельсия
			if (tempTemp > -50 && tempTemp < 120) return tempTemp;
			return DEVICE_ERROR;
		}
		
};
