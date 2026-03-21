#ifndef ROOM_H
#define ROOM_H

#include "DeviceManager.h"
#include "DeviceType.h"
#include "SmartDevice.h"
#include <memory>
#include <string>
#include <vector>

class Room {
private:
    static int nextId;

    int id;
    std::string name;
    std::vector<std::unique_ptr<SmartDevice>> devices;
    DeviceManager deviceManager;

public:
    explicit Room(const std::string& name);

    int getRoomId() const;
    std::string getName() const;

    bool addDeviceToRoom(DeviceType type, const std::string& deviceName = "");
    bool removeDevice(int deviceId);

    SmartDevice* getDevice(int deviceId) const;
    SmartDevice* getDevice(const std::string& deviceName) const;
    std::vector<SmartDevice*> getDevices(DeviceType type) const;
    std::vector<SmartDevice*> getAllDevices() const;

    void listDevices() const;

    void turnOnDevice(int deviceId);
    void turnOffDevice(int deviceId);
    void turnOnAllDevices();
    void turnOffAllDevices();

    void increaseDeviceTemperature(int deviceId, int amount);
    void decreaseDeviceTemperature(int deviceId, int amount);
    int getDeviceTemperature(int deviceId) const;
    void lockDevice(int deviceId);
    void unlockDevice(int deviceId);
    bool isDeviceLocked(int deviceId) const;

    void setLightBrightness(int deviceId, int level);
    void setTvVolume(int deviceId, int level);
    void setTvChannel(int deviceId, int channel);
    void connectComputerInternet(int deviceId);
};

#endif