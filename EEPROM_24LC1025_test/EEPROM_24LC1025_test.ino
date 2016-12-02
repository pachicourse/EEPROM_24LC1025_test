#include <Wire.h>
 
#define EPR_ADDR 0x51  // EEPROM address A2=Low,A1=Low,A0=HIGH
 
void setup() {
  SerialUSB.begin(9600);  // モニタ用にメッセージを出力
  while(!SerialUSB){
    ;
  }
  SerialUSB.println("EEPROM Test");
 
  Wire.begin();       // I2C master
  delay(1000);
  
  byte b[] = {5,10,20,40,80,160};
  int len = sizeof(byte);

//  eprWrite(0, b, len);
//  eprRead(0, len);
}

void loop() {
}


int eprWrite(int addr, byte b[], int l) {
  int ans;

  Wire.beginTransmission(EPR_ADDR);
  Wire.write(highByte(addr));
  Wire.write(lowByte(addr));
  Wire.write(b, l);
  ans = Wire.endTransmission();
  
  delay(5);
  return ans;
}
 
void eprRead(int addr, int l) {
  byte ret;
  
  Wire.beginTransmission(EPR_ADDR);
  Wire.write(highByte(addr));
  Wire.write(lowByte(addr));
  Wire.endTransmission();
  Wire.requestFrom(EPR_ADDR, l);
 
  while (Wire.available()) {
    ret = Wire.read();
    SerialUSB.println(ret);
  }
  return;
}
