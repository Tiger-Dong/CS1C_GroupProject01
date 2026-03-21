#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "SmartDevice.h"

class DeviceManager {
public:
    void turnOn(SmartDevice* device) const;
    void turnOff(SmartDevice* device) const;

    void increaseTemperature(SmartDevice* device, int amount) const;
    void decreaseTemperature(SmartDevice* device, int amount) const;
    int getTemperature(SmartDevice* device) const;

    void lock(SmartDevice* device) const;
    void unlock(SmartDevice* device) const;
    bool isLocked(SmartDevice* device) const;

    void setLightBrightness(SmartDevice* device, int level) const;
    void setTvVolume(SmartDevice* device, int level) const;
    void setTvChannel(SmartDevice* device, int channel) const;
    void connectComputerInternet(SmartDevice* device) const;
};

#endif
