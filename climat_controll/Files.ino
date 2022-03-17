void save(){
  EEPROM.update(0, 0);
  EEPROM.put(1, setting);
  Serial.println("Saved");
}
void load(){
  if(EEPROM[0] == 255) return;
  EEPROM.get(1, setting);
  
  updatePID();
  
  Serial.println("Loaded");
}
void resetSave(){
  EEPROM.update(0, 255);
  Serial.println("Save reset");
}
