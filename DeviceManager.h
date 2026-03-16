#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "SmartDevice.h"
#include <memory>
#include <string>
#include <vector>

class Light;
class TV;
class Computer;

// Central manager for polymorphic smart devices.
class DeviceManager {
private:
    std::vector<std::unique_ptr<SmartDevice>> devices;

    SmartDevice* findDeviceByName(const std::string& name);

public:
    void addDevice(std::unique_ptr<SmartDevice> device);

    void listAllDevices() const;
    void listDevicesInRoom(const std::string& roomName) const;
    void turnOnAll();
    void turnOffAll();
    void turnOnRoom(const std::string& roomName);
    void turnOffRoom(const std::string& roomName);

    bool setLightBrightness(const std::string& name, int level);
    bool setTvVolume(const std::string& name, int level);
    bool setTvChannel(const std::string& name, int channel);
    bool connectComputerInternet(const std::string& name);
};

#endif
