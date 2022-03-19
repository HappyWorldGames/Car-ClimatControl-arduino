void save(){
  EEPROM.update(0, 0); // Записываем в первую ячейку 0, потому что по умолчанию там 255
  EEPROM.put(1, setting); // Записываем настройки
  Serial.println("Saved");
}
void load(){
  if(EEPROM[0] == 255) return; // Проверяем первую ячейку памяти, если она равна 255, то нечего не делаем
  EEPROM.get(1, setting); // Если не равна 255, то читаем настройки
  
  updatePID();
  
  Serial.println("Loaded");
}
void resetSave(){
  EEPROM.update(0, 255); // Записываем в первую ячейку 255, обнуляя ячейку
  Serial.println("Save reset");
}
