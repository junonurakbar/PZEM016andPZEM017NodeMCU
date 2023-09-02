void lcdSetup(){
  lcd.begin();
  lcd.backlight();

  //create custom characters
  lcd.createChar(0, check);
  lcd.createChar(1, charSD);
  lcd.createChar(2, sinyal);
  lcd.createChar(3, upload);

  lcd.clear();
  timeClient.begin();
  timeClient.setTimeOffset(3600 * 7);
}

void sdCardSetup() {
  if (!SD.begin(chipSelect)) {
    lcd.setCursor(19, 2);
    lcd.print("X");
    // don't do anything more:
    return;
  }
  lcd.setCursor(19, 2);
  lcd.write(byte(1));
}

void lcdLoop(){
  currentMillisLCD = millis();
  if ( currentMillisLCD - startMillisLCD >= 1000 ){
    
    if (WiFi.status() == WL_CONNECTED){
      ambilDataNTP();
      ConvertNTPtoInt();
      ConvertNTPtoByteRTC();
      setRTC();
    }
    now = RTC.now();
    timeStamp = "";
    dayStamp = "";
    
    dayStamp = String(now.year());
    dayStamp += "-";
    if (now.month() < 10) {
      dayStamp += "0";
    }    
    dayStamp += String(now.month());
    dayStamp += "-";
    if (now.day() < 10) {
      dayStamp += "0";
    }
    dayStamp += String(now.day());

    if (now.hour() < 10){
      timeStamp += "0";
    }
    timeStamp += String(now.hour());
    timeStamp += ":";
    if (now.minute() < 10){
      timeStamp += "0";
    }
    timeStamp += String(now.minute());
    timeStamp += ":";
    if (now.second() < 10) {
      timeStamp += "0";
    }
    timeStamp += String(now.second());
    
    DisplayRTCtoLCD();
    DisplayPZEMACtoLCD();
    DisplayPZEMDCtoLCD();

    //reset pzem pas jam 8.00 pagi atau jam 16.10

//    if ((now.hour()==8 && now.minute()==0) || (now.hour() == 17 && now.minute() == 0)){
//      resetEnergy(0x01);
//      resetEnergy(0x02);
//    }
    
    startMillisLCD = currentMillisLCD;
    statePZEM = !statePZEM;
  }
}

void DisplayRTCtoLCD() {
  //display dd/mm/yyyy
  if (now.day() > 9){
    lcd.setCursor(0,3);
    lcd.print(now.day());
  }
  else {
    lcd.setCursor(0,3);
    lcd.print("0");
    lcd.print(now.day());
  }
  lcd.setCursor(2,3);
  lcd.print('/');
  if (now.month() > 9) {
    lcd.setCursor(3,3);
    lcd.print(now.month());
  }
  else {
    lcd.setCursor(3,3);
    lcd.print("0");
    lcd.print(now.month());
    }
  lcd.setCursor(5,3);
  lcd.print('/');
  lcd.setCursor(6,3);
  lcd.print(now.year());
  //  display hh:mm:ss
  if( now.hour() > 9 ) {      
    lcd.setCursor(11,3);
    lcd.print(now.hour());
  } else {
    lcd.setCursor(11,3);
    lcd.print("0");
    lcd.print(now.hour());
  }
  lcd.setCursor(13,3);
  lcd.print(':');
  if (now.minute() > 9) {
    lcd.setCursor(14,3);
    lcd.print(now.minute()); }
  else {
    lcd.setCursor(14,3);
    lcd.print("0");
    lcd.print(now.minute());
    }
  lcd.setCursor(16,3);
  lcd.print(':');
  if(now.second() > 9){
    lcd.setCursor(17,3);
    lcd.print(now.second());
  }
  else {
    lcd.setCursor(17,3);
    lcd.print("0");
    lcd.print(now.second()); 
  }
}

void DisplayPZEMACtoLCD() {
  //Display PZEM AC
  lcd.setCursor(0,0);
  lcd.print(Vac, 1);
  lcd.print("V"); //220.2V
  lcd.setCursor(7,0);
  lcd.print(Iac,3);
  lcd.print("A"); //2.18A
  lcd.setCursor(14,0);
  lcd.print(Pac,1);
  lcd.print("W");
  lcd.setCursor(0,2);
  lcd.print(Eac,0);
  lcd.print("Wh");
}

void DisplayPZEMDCtoLCD() {
  //Display PZEM DC
  lcd.setCursor(0,1);
  lcd.print(Vdc, 1);
  lcd.print("V"); //150.2V
  lcd.setCursor(7,1);
  lcd.print(Idc,1);
  lcd.print("A"); //2.18A
  lcd.setCursor(14,1);
  lcd.print(Pdc,1);
  lcd.print("W");
  lcd.setCursor(8,2);
  lcd.print(Edc,0);
  lcd.print("Wh");
}
