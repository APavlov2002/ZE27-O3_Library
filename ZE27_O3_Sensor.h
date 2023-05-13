#ifndef ZE27_O3_SENSOR_H
#define ZE27_O3_SENSOR_H

#include <Wire.h>
#include <SD.h>

class ZE27_O3_Sensor {
    public:
        ZE27_O3_Sensor(int addr);
        float readConcentration();
        void saveToSD(float ppmO3);
    private:
        int _addr;
        File _dataFile;
};

#endif