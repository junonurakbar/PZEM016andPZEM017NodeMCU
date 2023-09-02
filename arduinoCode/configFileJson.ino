void saveJson() {
  File file = SD.open(filename, FILE_WRITE);
  if (!file) {
//    Serial.println(F("Failed to create file"));
    lcd.setCursor(19, 2);
    lcd.print("X");
    return;
  }
  lcd.setCursor(19, 2);
  lcd.write(byte(1));
  
  StaticJsonDocument<256> doc;

  // Set the values in the document
  doc["dayStamp"] = dayStamp;
  doc["timeStamp"] = timeStamp;
  doc["Vac"] = String(Vac);
  doc["Iac"] = String(Iac);
  doc["Pac"] = String(Pac);
  doc["Eac"] = String(Eac);
  doc["Vdc"] = String(Vdc);
  doc["Idc"] = String(Idc,1);
  doc["Pdc"] = String(Pdc,1);
  doc["Edc"] = String(Edc);

  // Serialize JSON to file
  if (serializeJson(doc, file) == 0) {
  }
  file.println();
  file.close();
}
