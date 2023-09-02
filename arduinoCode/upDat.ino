void upDat() {
  WiFiClient client;
  HTTPClient http;
  String url, nodemcuData;

  StaticJsonDocument<512> doc;
  url = "http://192.168.254.60/DBTA/api.php";

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

  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");

  if (!http.begin(client, url)) {
    Serial.println("connection failed");
    lcd.setCursor(17, 2);
    lcd.print("X");
    return;
  }

  serializeJson(doc, nodemcuData);
  Serial.print("POST data >> ");
  Serial.println(nodemcuData);

  int httpCode = http.POST(nodemcuData);
  String payload;
  if (httpCode > 0) {
    payload = http.getString();
    payload.trim();
    if (payload.length() > 0) {
      Serial.println(payload + "\n");
      lcd.setCursor(17, 2);
      lcd.write(byte(3));
      lcd.setCursor(19,2);
      lcd.print(" ");
    } else {
      lcd.setCursor(17, 2);
      lcd.print("X");
      saveJson();
    }
  }
  http.end();
  Serial.println(payload);
}
