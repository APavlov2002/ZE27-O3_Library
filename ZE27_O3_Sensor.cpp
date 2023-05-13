#include "ZE27_O3.h"

ZE27_O3_Sensor::ZE27_O3_Sensor(int addr) {
    _addr = addr;
    Wire.begin();
    SD.begin(SS);
    _dataFile = SD.open("data.txt", FILE_WRITE);
}

float ZE27_O3_Sensor::readConcentration() {
    Wire.beginTransmission(_addr);
    Wire.write(0x78);
    Wire.endTransmission();

    delay(100);

    Wire.requestFrom(_addr, 7);

    byte buffer[7];
    for(int i = 0; i < 7; i++) {
        buffer[i] = Wire.read();
    }

    if(buffer[0] == 0xFF && buffer[1] == 0x17) {
        float ppmO3 = buffer[2] << 8 | buffer[3];
        ppmO3 /= 1000;
        return ppmO3;
    } else {
        return -1;
    }
}

void ZE27_O3_Sensor::saveToSD(float ppmO3) {
    _dataFile.println(ppmO3);
    _dataFile.flush();
}		

void ZE27_O3_Sensor::printToSerial(float ppmO3) {
  Serial.print("Concentration: ");
  Serial.println(ppmO3);
}