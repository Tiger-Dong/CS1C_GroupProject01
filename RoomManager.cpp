#include "RoomManager.h"

void RoomManager::addDevice(std::unique_ptr<SmartDevice> device) {
    deviceManager.addDevice(std::move(device));
}

void RoomManager::listAllDevices() const {
    deviceManager.listAllDevices();
}

void RoomManager::listDevicesInRoom(const std::string& roomName) const {
    deviceManager.listDevicesInRoom(roomName);
}

void RoomManager::turnOnAll() {
    deviceManager.turnOnAll();
}

void RoomManager::turnOffAll() {
    deviceManager.turnOffAll();
}

void RoomManager::turnOnRoom(const std::string& roomName) {
    deviceManager.turnOnRoom(roomName);
}

void RoomManager::turnOffRoom(const std::string& roomName) {
    deviceManager.turnOffRoom(roomName);
}

bool RoomManager::setLightBrightness(const std::string& name, int level) {
    return deviceManager.setLightBrightness(name, level);
}

bool RoomManager::setTvVolume(const std::string& name, int level) {
    return deviceManager.setTvVolume(name, level);
}

bool RoomManager::setTvChannel(const std::string& name, int channel) {
    return deviceManager.setTvChannel(name, channel);
}

bool RoomManager::connectComputerInternet(const std::string& name) {
    return deviceManager.connectComputerInternet(name);
}
