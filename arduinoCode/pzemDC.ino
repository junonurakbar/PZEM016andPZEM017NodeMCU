void pzemDCLoop() {
  
//  if (a == 1){
    
//    setShunt(0x02);
//      lcd.setCursor(15,2);
//      lcd.print("D");
    node2.begin(pzemSlaveAddrDC, PZEMSerial);  
//    if (currentMillisPZEM - startMillisPZEM >= 1000){
      
      uint8_t resultDC;                                                                                    
      resultDC = node2.readInputRegisters(0x0000, 6);                                                    
      if (resultDC == node2.ku8MBSuccess) {                                                               
        uint32_t tempdouble = 0x00000000;                                                           
        VdcRaw = node2.getResponseBuffer(0x0000) / 100.0;                                      
        IdcRaw = node2.getResponseBuffer(0x0001) / 100.0;                                       
        tempdouble =  (node2.getResponseBuffer(0x0003) << 16) + node2.getResponseBuffer(0x0002);      
        PdcRaw = tempdouble / 10.0;                                                             
        tempdouble =  (node2.getResponseBuffer(0x0005) << 16) + node2.getResponseBuffer(0x0004);      
        EdcRaw = tempdouble;

        //kalibruhsi
        if (VdcRaw >= 75 && VdcRaw <95){
          Vdc = VdcRaw - 1;
        }
        else if (VdcRaw >= 95 && VdcRaw <=125){
          Vdc = VdcRaw - 1.4;
        }
        else if (Vdc > 125 && Vdc <=150){
          Vdc = VdcRaw - 1.75;
        }
        else {Vdc = VdcRaw;}
//        Idc = IdcRaw/2;
//        Pdc = Vdc*Idc;
//        Edc = EdcRaw;

        Idc = IdcRaw;
        Pdc = PdcRaw;
        Edc = EdcRaw;
        
        lcd.setCursor(16,2);
        lcd.write(byte(0));
        statePZEM = !statePZEM;                                                                  
      }
      else {
        lcd.setCursor(16,2);
        lcd.print("X");
        statePZEM = !statePZEM;
      }
      if (pzemSlaveAddrDC==5)                                                                          
          {}
      else
          {}
//      a = 0;  
//      startMillisPZEM = currentMillisPZEM - 1000;
//    }
    
//  }
}

void setShunt(uint8_t slaveAddr) {                                                                           
  static uint8_t SlaveParameter = 0x06;                                                             
  static uint16_t registerAddress = 0x0003;                                                         
  
  uint16_t u16CRC = 0xFFFF;                                                                        
  u16CRC = crc16_update(u16CRC, slaveAddr);                                                       
  u16CRC = crc16_update(u16CRC, SlaveParameter);
  u16CRC = crc16_update(u16CRC, highByte(registerAddress));
  u16CRC = crc16_update(u16CRC, lowByte(registerAddress));
  u16CRC = crc16_update(u16CRC, highByte(NewshuntAddr));
  u16CRC = crc16_update(u16CRC, lowByte(NewshuntAddr));

  preTransmission();                                                                             

  PZEMSerial.write(slaveAddr);                                                       
  PZEMSerial.write(SlaveParameter);
  PZEMSerial.write(highByte(registerAddress));
  PZEMSerial.write(lowByte(registerAddress));
  PZEMSerial.write(highByte(NewshuntAddr));
  PZEMSerial.write(lowByte(NewshuntAddr));
  PZEMSerial.write(lowByte(u16CRC));
  PZEMSerial.write(highByte(u16CRC));
  delay(10);
  postTransmission();                                                       
  delay(100);
  while (PZEMSerial.available())   
    {   
    }
}
