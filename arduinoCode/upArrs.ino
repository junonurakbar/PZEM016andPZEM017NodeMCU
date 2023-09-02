void upArrs() {
  // Open the file
  File file = SD.open("backup.txt");
  if (!file) {
//    Serial.println("Failed to open file");
    return;
  }
  
  // Create a JSON array to hold the objects
  DynamicJsonDocument doc(4096);
  JsonArray jsonArray = doc.to<JsonArray>();
  
  // Read and process each line
  while (file.available()) {
    String line = file.readStringUntil('\n');
  
    // Parse the JSON object
    DynamicJsonDocument objDoc(512);
    DeserializationError error = deserializeJson(objDoc, line);
    if (error) {
//      Serial.print("Failed to parse JSON: ");
//      Serial.println(error.c_str());
      continue;
    }
  
    // Add the object to the array
    jsonArray.add(objDoc.as<JsonObject>());
  }
  
  // Close the file
  file.close();
  
  // Convert the JSON array to a string
  String dataString;
  serializeJson(doc, dataString);
  String serverUrl = "http://192.168.254.60/DBTA/api_sd.php";
  
  // Create an HTTP client object
  HTTPClient http;
  
  // Specify the target URL and headers
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");
    
  // Make the POST request and get the response
  int httpResponseCode = http.POST(dataString);
  String response;
  
  if (httpResponseCode > 0) {
    response = http.getString();
    lcd.setCursor(19,2);
    lcd.write(byte(3));
    SD.remove("backup.txt");
  } else {
    saveJson();
  }
  http.end();
}
