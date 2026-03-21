#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include "DeviceType.h"
#include "Room.h"
#include <string>
#include <vector>

class RoomManager {
private:
    std::vector<Room> rooms;

public:
    int createRoom(const std::string& roomName);
    Room* getRoom(int roomId);
    const Room* getRoom(int roomId) const;
    bool removeRoom(int roomId);

    bool addDeviceToRoom(int roomId, DeviceType type, const std::string& deviceName = "");
    bool removeDeviceFromRoom(int roomId, int deviceId);

    void listRooms() const;
    void listAllDevices() const;
    void listDevicesInRoom(int roomId) const;

    void turnOnAll();
    void turnOffAll();
    bool turnOnRoom(int roomId);
    bool turnOffRoom(int roomId);
    bool turnOnDevice(int roomId, int deviceId);
    bool turnOffDevice(int roomId, int deviceId);

    bool increaseDeviceTemperature(int roomId, int deviceId, int amount);
    bool decreaseDeviceTemperature(int roomId, int deviceId, int amount);
    bool lockDevice(int roomId, int deviceId);
    bool unlockDevice(int roomId, int deviceId);
    bool isDeviceLocked(int roomId, int deviceId, bool& locked) const;

    bool setLightBrightness(int roomId, int deviceId, int level);
    bool setTvVolume(int roomId, int deviceId, int level);
    bool setTvChannel(int roomId, int deviceId, int channel);
    bool connectComputerInternet(int roomId, int deviceId);
};

#endif
