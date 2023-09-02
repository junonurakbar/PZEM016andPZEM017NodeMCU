void pzemSetup(){
//  startMillisPZEM = millis();                 /* Start counting time for run code */
  PZEMSerial.begin(9600,SWSERIAL_8N1,3,1);
  
  pinMode(MAX485_RE, OUTPUT);                 /* Define RE Pin as Signal Output for RS485 converter. Output pin means Arduino command the pin signal to go high or low so that signal is received by the converter*/
  pinMode(MAX485_DE, OUTPUT);                 /* Define DE Pin as Signal Output for RS485 converter. Output pin means Arduino command the pin signal to go high or low so that signal is received by the converter*/
  digitalWrite(MAX485_RE, 0);                 /* Arduino create output signal for pin RE as LOW (no output)*/
  digitalWrite(MAX485_DE, 0);                 /* Arduino create output signal for pin DE as LOW (no output)*/
                                              // both pins no output means the converter is in communication signal receiving mode
  node.preTransmission(preTransmission);                /* Callbacks allow us to configure the RS485 transceiver correctly*/
  node.postTransmission(postTransmission);
  node2.preTransmission(preTransmission);                // Callbacks allow us to configure the RS485 transceiver correctly
  node2.postTransmission(postTransmission);
                                              // By default I allow this code to run every program startup. Will not have effect if you only have 1 meter
//    resetEnergy(0x01);                      // By delete the double slash symbol, the Energy value in the meter is reset.
//    resetEnergy(0x02); 
  startMillisLCD = millis();
}

void pzemACLoop() {                                                                     /* count time for program run every second (by default)*/
            
//  if (a == 0) {
    node.begin(pzemSlaveAddrAC, PZEMSerial);  
//    lcd.setCursor(15,2);
//    lcd.print("A");
    
//    if (currentMillisPZEM - startMillisPZEM >= 1000) {                                        /* for every x seconds, run the codes below*/
      /* Define and start the Modbus RTU communication. Communication to specific slave address and which Serial port */
      uint8_t resultAC;                                                                                 /* Declare variable "result" as 8 bits */   
      resultAC = node.readInputRegisters(0x0000, 6);                                                    /* read the 9 registers (information) of the PZEM-014 / 016 starting 0x0000 (voltage information) kindly refer to manual)*/
      if (resultAC == node.ku8MBSuccess)                                                                /* If there is a response */
        {
        
        uint32_t tempdouble2 = 0x00000000;                                                           /* Declare variable "tempdouble" as 32 bits with initial value is 0 */ 
        VacRaw = node.getResponseBuffer(0x0000) / 10.0;                                        /* get the 16bit value for the voltage value, divide it by 10 (as per manual) */
                                                                                                    // 0x0000 to 0x0008 are the register address of the measurement value
        //kalibruhsi
        if (VacRaw >= 155 && VacRaw < 180){
          Vac = VacRaw - 0.5;
        }
  
        else if (VacRaw >= 180 && VacRaw < 200) {
          Vac = VacRaw - 0.8;
        }
  
        else if(VacRaw >= 200 && VacRaw <= 250) {
          Vac = VacRaw - 1;
        }
  
        else {
          Vac = VacRaw;
        }
        
        tempdouble2 =  (node.getResponseBuffer(0x0002) << 16) + node.getResponseBuffer(0x0001);      /* get the currnet value. Current value is consists of 2 parts (2 digits of 16 bits in front and 2 digits of 16 bits at the back) and combine them to an unsigned 32bit */
        Iac = tempdouble2 / 1000.00;                                                         /* Divide the value by 1000 to get actual current value (as per manual) */
        
        tempdouble2 =  (node.getResponseBuffer(0x0004) << 16) + node.getResponseBuffer(0x0003);      /* get the power value. Power value is consists of 2 parts (2 digits of 16 bits in front and 2 digits of 16 bits at the back) and combine them to an unsigned 32bit */
        Pac = tempdouble2 / 10.0;                                                              /* Divide the value by 10 to get actual power value (as per manual) */
        
        tempdouble2 =  (node.getResponseBuffer(0x0006) << 16) + node.getResponseBuffer(0x0005);      /* get the energy value. Energy value is consists of 2 parts (2 digits of 16 bits in front and 2 digits of 16 bits at the back) and combine them to an unsigned 32bit */
        Eac = tempdouble2;                                                                    
                
        lcd.setCursor(18,2);
        lcd.write(byte(0));
        
        
        if (pzemSlaveAddrAC==2){                                                                       /* just for checking purpose to see whether can read modbus*/
                              }
        statePZEM = !statePZEM;
        }
         
        else
          {
          // lcd.clear();
          lcd.setCursor(18,2);
          lcd.print("X");
          statePZEM = !statePZEM;
          }
//      a = 1;  
//      startMillisPZEM = currentMillisPZEM - 1000;
//    }
    
//  }
  
}
