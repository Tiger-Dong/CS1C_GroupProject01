#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include "DeviceManager.h"
#include <memory>
#include <string>

// Top-level coordinator for room-oriented operations.
class RoomManager {
private:
    DeviceManager deviceManager;

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
