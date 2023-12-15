# Solar Panel Monitoring 
Solar Power monitoring using Arduino, MySQL, and Apache

# Disclaimer!
I assume that you have knowledge about electrical in photovoltaic system because you will deal with high voltage to measure solar panel and i will take no responsibilities if something happened to you. Safety comes first '-')/

# Tools Requirements
  - NodeMCU ESP8266
  - RTC DS3231
  - LCD 20x4 I2C
  - PZEM-016
  - PZEM-017
  - MAX485 module
  - micro SD card module reader/writer
  - micro SD <= 2 GB or micro SD SDHC <= 32 GB

# Applications you will need
  - Arduino IDE
  - XAMPP

# Arduino Libraries
  - RTC DS3231 by Andrew Wickert (Arduino IDE -> Skecth -> Include Library -> Manage Libraries)
  - NTP Client library forked by Taranais
  - ModbusMaster Library
  - ESP8266 Boards (http://arduino.esp8266.com/stable/package_esp8266com_index.json)

# Hardware Schematic
Please turn off all the power before you connect the components. Any exposed conductors need to be isolated and fused 
![image](https://github.com/junonurakbar/PZEM016andPZEM017NodeMCU/assets/111905396/daf4d857-0464-4a29-9178-e3a978287b80)
