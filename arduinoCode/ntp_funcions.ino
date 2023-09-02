void ambilDataNTP (){
  if (WiFi.status() == WL_CONNECTED) {
    timeClient.update();
  }
  else {}
  formattedDate = timeClient.getFormattedDate();
  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  int splitT = formattedDate.indexOf("T");
//  dayStamp = formattedDate.substring(0, splitT);;
  // Extract time
//  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);

  //ambil tahun, bulan, hari, jam, menit, detik 
  //DATE: YYYY-MM-DD, YYYY: year, MM: month, DD: Date
  tahun = dayStamp.substring(0, 4);
  bulan = dayStamp.substring(5, 7);
  hari = dayStamp.substring(8, 10);

  //HOUR: HH-MM-SS, HH; Hour, MM: Minute, SS: Second
  jam = timeStamp.substring(0, 2);
  menit = timeStamp.substring(3, 5);
  detik = timeStamp.substring(6, timeStamp.length());
}

void ConvertNTPtoInt() {
  //taking datas from NTP and convert them into integer
  Year = tahun.toInt();
  Month = bulan.toInt();
  Day = hari.toInt();
  Hour = jam.toInt();
  Minute = menit.toInt();
  Second = detik.toInt();
}

void ConvertNTPtoByteRTC(){
  year = byte(Year) - 48;
  month = byte(Month);
  date = byte(Day);
  hour = byte(Hour);
  minute = byte(Minute);
  second = byte(Second);
}

void setRTC() {
  rtc.setYear(year);
  rtc.setMonth(month);
  rtc.setDate(date);
  rtc.setHour(hour);
  rtc.setMinute(minute);
  rtc.setSecond(second);
}
