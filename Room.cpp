#include "Room.h"

#include "DeviceFactory.h"
#include <iostream>

int Room::nextId = 0;

Room::Room(const std::string& name)
    : id(nextId++), name(name) {}

int Room::getRoomId() const {
    return id;
}

std::string Room::getName() const {
    return name;
}

bool Room::addDeviceToRoom(DeviceType type, const std::string& deviceName) {
    if (type == DeviceType::NONE) {
        return false;
    }

    const std::string effectiveName = deviceName.empty() ? to_string(type) : deviceName;
    std::unique_ptr<SmartDevice> device = DeviceFactory::createDevice(type, effectiveName, name);
    if (!device) {
        return false;
    }

    devices.push_back(std::move(device));
    return true;
}

bool Room::removeDevice(int deviceId) {
    if (deviceId < 0 || deviceId >= static_cast<int>(devices.size())) {
        return false;
    }

    devices.erase(devices.begin() + deviceId);
    return true;
}

SmartDevice* Room::getDevice(int deviceId) const {
    if (deviceId < 0 || deviceId >= static_cast<int>(devices.size())) {
        return nullptr;
    }
    return devices[deviceId].get();
}

SmartDevice* Room::getDevice(const std::string& deviceName) const {
    for (const auto& device : devices) {
        if (device->getName() == deviceName) {
            return device.get();
        }
    }
    return nullptr;
}

std::vector<SmartDevice*> Room::getDevices(DeviceType type) const {
    std::vector<SmartDevice*> matches;
    for (const auto& device : devices) {
        if (device->getType() == type) {
            matches.push_back(device.get());
        }
    }
    return matches;
}

std::vector<SmartDevice*> Room::getAllDevices() const {
    std::vector<SmartDevice*> result;
    for (const auto& device : devices) {
        result.push_back(device.get());
    }
    return result;
}

void Room::listDevices() const {
    if (devices.empty()) {
        std::cout << "  No devices in this room." << std::endl;
        return;
    }

    for (int index = 0; index < static_cast<int>(devices.size()); ++index) {
        std::cout << "  Device [" << index << "]" << std::endl;
        devices[index]->printStatus();
    }
}

void Room::turnOnDevice(int deviceId) {
    deviceManager.turnOn(getDevice(deviceId));
}

void Room::turnOffDevice(int deviceId) {
    deviceManager.turnOff(getDevice(deviceId));
}

void Room::turnOnAllDevices() {
    for (const auto& device : devices) {
        if (dynamic_cast<PowerInterface*>(device.get())) {
            deviceManager.turnOn(device.get());
        }
    }
}

void Room::turnOffAllDevices() {
    for (const auto& device : devices) {
        if (dynamic_cast<PowerInterface*>(device.get())) {
            deviceManager.turnOff(device.get());
        }
    }
}

void Room::increaseDeviceTemperature(int deviceId, int amount) {
    deviceManager.increaseTemperature(getDevice(deviceId), amount);
}

void Room::decreaseDeviceTemperature(int deviceId, int amount) {
    deviceManager.decreaseTemperature(getDevice(deviceId), amount);
}

int Room::getDeviceTemperature(int deviceId) const {
    return deviceManager.getTemperature(getDevice(deviceId));
}

void Room::lockDevice(int deviceId) {
    deviceManager.lock(getDevice(deviceId));
}

void Room::unlockDevice(int deviceId) {
    deviceManager.unlock(getDevice(deviceId));
}

bool Room::isDeviceLocked(int deviceId) const {
    return deviceManager.isLocked(getDevice(deviceId));
}

void Room::setLightBrightness(int deviceId, int level) {
    deviceManager.setLightBrightness(getDevice(deviceId), level);
}

void Room::setTvVolume(int deviceId, int level) {
    deviceManager.setTvVolume(getDevice(deviceId), level);
}

void Room::setTvChannel(int deviceId, int channel) {
    deviceManager.setTvChannel(getDevice(deviceId), channel);
}

void Room::connectComputerInternet(int deviceId) {
    deviceManager.connectComputerInternet(getDevice(deviceId));
}