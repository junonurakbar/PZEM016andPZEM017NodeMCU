#include <Wire.h>
#include <SPI.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>
#include <ModbusMaster.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//const char *ssid = "HOTSPOT-ITENAS";
//const char *password = "";
const char *ssid     = "awikwok";
const char *password = "Kne3-H0W*";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

//IP Address Server yang terpasang XAMPP
//const char *host = "192.168.140.60";

String formattedDate, dayStamp, timeStamp;
String tahun, bulan, hari, jam, menit, detik;
int Year, Month, Day, Hour, Minute, Second;
byte year, month, date, hour, minute, second;
DateTime now; //bikin variabel "now" agar RTC dapat hitung waktu
unsigned long startMillisWifi,currentMillisWifi;
//const unsigned long periodWifi = 60000;

File myFile;
const int chipSelect = 15; //D8
String stringData = ""; //data buat dimasukin ke SD atau diupload

byte check[] = {
  B00000,
  B00000,
  B00001,
  B00010,
  B10100,
  B01000,
  B00000,
  B00000
};

byte charSD[] = {
  B00000,
  B11111,
  B10111,
  B11111,
  B10001,
  B10001,
  B01110,
  B00000
};

byte sinyal[] = {
  B00000,
  B00000,
  B00000,
  B00001,
  B00001,
  B00011,
  B00111,
  B01111
};

byte upload[] = {
  B00000,
  B00000,
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B00000
};

LiquidCrystal_I2C lcd(0x27, 20, 4);
RTClib RTC;
DS3231 rtc;

//initialize pzem ac
SoftwareSerial PZEMSerial;
#define MAX485_DE 2 // Define DE Pin to Arduino pin. Connect DE Pin of Max485 converter module to D4 NodeMCU
#define MAX485_RE 0 // Define RE Pin to Arduino pin. Connect RE Pin of Max485 converter module to D3 NodeMCU
static uint8_t pzemSlaveAddrAC = 0x01;
static uint8_t pzemSlaveAddrDC = 0x02;       
static uint16_t NewshuntAddr = 0x0001; //adress shunt, 0x0000 for 100A, 0x0001 for 50 A, 0x0002 200 A, 0x0003 300 A;

ModbusMaster node;                          /* activate modbus master codes*/  
ModbusMaster node2;

float Vac, Iac, Pac, Eac;                       /* Declare value for AC voltage */                            /* Declare value for power factor */
float VacRaw, IacRaw;

float VdcRaw, IdcRaw, PdcRaw, EdcRaw;
float Vdc, Idc, Pdc, Edc;

unsigned long startMillisPZEM, currentMillisPZEM, startMilliSetShunt;              /* start counting time for LCD Display */
//const unsigned long periodPZEM = 2000;      // refresh every X seconds (in seconds) in LED Display. Default 1000 = 1 second

unsigned long startMillisLCD, currentMillisLCD;
//const unsigned long periodLCD = 1000;
int ResetEnergyAC, ResetEnergyDC, a;

const char *filename = "backup.txt";  // <- SD library uses 8.3 filenames

bool statePZEM = 0; //if state = 0 -> PZEM016 runs; if state = 1 -> PZEM017 runs 
//const int flashButton = 0;

void setup() {
//  Serial.begin(4800);
  Wire.begin();
  pzemSetup();
  wifiSetup();
  sdCardSetup();
  lcdSetup();
//  pinMode(flashButton, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcdLoop();
  currentMillisPZEM = millis();
  if (currentMillisPZEM - startMillisPZEM >= 1000){
    if (statePZEM) {
      lcd.setCursor(15,2);
      lcd.print("D");
      pzemACLoop();
      //jam 4 sore sama jam 8 pagi diset reset energy
      if ((now.hour() == 16 && now.minute() == 0)||
         (now.hour() == 9 && now.minute() == 16)){
        resetEnergy(0x02);
        lcd.setCursor(0,2);
        lcd.print("              ");
      }
      statePZEM = !statePZEM;
    }
    else {
      lcd.setCursor(15,2);
      lcd.print("A");
      pzemDCLoop();
      //jam 4 sore sama jam 8 pagi diset reset energy
      if ((now.hour() == 16 && now.minute() == 00)||
         (now.hour() == 9 && now.minute() == 16)){
        resetEnergy(0x01);
        lcd.setCursor(0,2);
        lcd.print("              ");
      }
      statePZEM = !statePZEM;
    }
    startMillisPZEM = currentMillisPZEM - 1000;
  }
  wifiLoop(); 
}
