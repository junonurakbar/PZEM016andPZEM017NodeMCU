void wifiSetup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    break;
  }
  
//  timeClient.begin();
//  timeClient.setTimeOffset(3600 * 7);
//  ambilDataNTP();
}

void wifiLoop() {
  currentMillisWifi = millis();
  if (currentMillisWifi - startMillisWifi >= 60000) {   
    if (WiFi.status() != WL_CONNECTED) {
      saveJson();
      lcd.setCursor(17, 2);
      lcd.print(" ");
    } 
    else {
      if (SD.exists("backup.txt")){
        upArrs();
      }
      else {
        upDat(); 
      }  
    }
    startMillisWifi = currentMillisWifi;
    statePZEM = !statePZEM;
  }
}
