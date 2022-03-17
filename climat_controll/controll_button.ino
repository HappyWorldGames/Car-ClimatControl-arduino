void initControllButton(){
  pinMode(RELAY_AIR_CONDITIONING_BUS, OUTPUT);
  pinMode(RELAY_AIR_RECIRCULATION_BUS, OUTPUT);
  Serial.println("InitControllButton ok");
}

boolean airRecirculationStatus = false;
void airRecirculation(boolean turnOn){
  if(turnOn == airRecirculationStatus) return;
  airRecirculationStatus = turnOn;
  Serial.print("airRecirculationStatus ");
  Serial.println(airRecirculationStatus);
  digitalWrite(RELAY_AIR_RECIRCULATION_BUS, airRecirculationStatus ? HIGH : LOW);
}

boolean airConditioningStatus = false;
void airConditioning(boolean turnOn){
  if(turnOn == airConditioningStatus) return;
  airConditioningStatus = turnOn;
  Serial.print("airConditioningStatus ");
  Serial.println(airConditioningStatus);
  digitalWrite(RELAY_AIR_CONDITIONING_BUS, airConditioningStatus ? HIGH : LOW);
}

void getStatusControllButton() {
  Serial.print("airRecirculationStatus ");
  Serial.println(airRecirculationStatus);

  Serial.print("airConditioningStatus ");
  Serial.println(airConditioningStatus);
}
