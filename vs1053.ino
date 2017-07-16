#include "rtpmidibridge.h"

void setup_vs1053() {
#ifdef USE_SPI_VS1053
    SPI.begin();
    pinMode(VS1053_XDCS,OUTPUT);
    digitalWrite(VS1053_XDCS,HIGH);
  
    pinMode(VS1053_RESET,OUTPUT);
    digitalWrite(VS1053_RESET,LOW);
    delay(10);
    digitalWrite(VS1053_RESET,HIGH);
#endif
}

void SPI3(int cmd, int one, int two) {
#ifdef USE_SPI_VS1053
  digitalWrite(VS1053_XDCS,LOW);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  SPI.transfer16(cmd);
  SPI.transfer16(one);
  SPI.transfer16(two);
  SPI.endTransaction();
  digitalWrite(VS1053_XDCS,HIGH);
#endif
}

void SPI2(int cmd, int one) {
#ifdef USE_SPI_VS1053
  digitalWrite(VS1053_XDCS,LOW);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  SPI.transfer16(cmd);
  SPI.transfer16(one);
  SPI.endTransaction();
  digitalWrite(VS1053_XDCS,HIGH);
#endif
}
