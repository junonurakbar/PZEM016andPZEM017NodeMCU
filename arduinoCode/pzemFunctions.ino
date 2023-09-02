void preTransmission()                                                                                   
{ 
  /* 1- PZEM-014/016 AC Energy Meter */       
  digitalWrite(MAX485_RE, 1);                                                                      
  digitalWrite(MAX485_DE, 1);                                                                       
  //delay(1);                                                                                        
}

void postTransmission()                                                                                  
{        
  
                                                                                        
  digitalWrite(MAX485_RE, 0);                                                                      
  digitalWrite(MAX485_DE, 0);                                                                       
}

void resetEnergy(uint8_t slaveAddr)                                                                  
{
  
  uint16_t u16CRC = 0xFFFF;                                                                         
  static uint8_t resetCommand = 0x42;                                                               
  u16CRC = crc16_update(u16CRC, slaveAddr);
  u16CRC = crc16_update(u16CRC, resetCommand);
  preTransmission();                                                                                  
  PZEMSerial.write(slaveAddr);                                                                     
  PZEMSerial.write(resetCommand);                                                                      
  PZEMSerial.write(lowByte(u16CRC));                                                                   
  PZEMSerial.write(highByte(u16CRC));                                                               

  postTransmission();                                                                          
        
  while (PZEMSerial.available())
    {break;                                                                      
    }
}
