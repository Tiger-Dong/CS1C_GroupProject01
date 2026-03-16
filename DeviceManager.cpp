#include "DeviceManager.h"

#include "Computer.h"
#include "Light.h"
#include "PowerInterface.h"
#include "TV.h"
#include "DeviceExceptions.h"

#include <iostream>

SmartDevice* DeviceManager::findDeviceByName(const std::string& name) {
    for (const auto& device : devices) {
        if (device->getName() == name) {
            return device.get();
        }
    }
    return nullptr;
}

void DeviceManager::addDevice(std::unique_ptr<SmartDevice> device) {
    if (!device) {
        return;
    }
    devices.push_back(std::move(device));
}

void DeviceManager::listAllDevices() const {
    for (const auto& device : devices) {
        device->displayStatus();
    }
}

void DeviceManager::listDevicesInRoom(const std::string& roomName) const {
    bool found = false;
    for (const auto& device : devices) {
        if (device->getLocation() == roomName) {
            device->displayStatus();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No devices found in room: " << roomName << std::endl;
    }
}

void DeviceManager::turnOnAll() {
    for (const auto& device : devices) {
        if (auto* power = dynamic_cast<PowerInterface*>(device.get())) {
            try {
                power->turnOn();
            } catch (const InvalidDeviceStateException& ex) {
                std::cout << "State error (" << device->getName() << "): " << ex.what() << std::endl;
            }
        }
    }
}

void DeviceManager::turnOffAll() {
    for (const auto& device : devices) {
        if (auto* power = dynamic_cast<PowerInterface*>(device.get())) {
            try {
                power->turnOff();
            } catch (const InvalidDeviceStateException& ex) {
                std::cout << "State error (" << device->getName() << "): " << ex.what() << std::endl;
            }
        }
    }
}

void DeviceManager::turnOnRoom(const std::string& roomName) {
    for (const auto& device : devices) {
        if (device->getLocation() != roomName) {
            continue;
        }

        if (auto* power = dynamic_cast<PowerInterface*>(device.get())) {
            try {
                power->turnOn();
            } catch (const InvalidDeviceStateException& ex) {
                std::cout << "State error (" << device->getName() << "): " << ex.what() << std::endl;
            }
        }
    }
}

void DeviceManager::turnOffRoom(const std::string& roomName) {
    for (const auto& device : devices) {
        if (device->getLocation() != roomName) {
            continue;
        }

        if (auto* power = dynamic_cast<PowerInterface*>(device.get())) {
            try {
                power->turnOff();
            } catch (const InvalidDeviceStateException& ex) {
                std::cout << "State error (" << device->getName() << "): " << ex.what() << std::endl;
            }
        }
    }
}

bool DeviceManager::setLightBrightness(const std::string& name, int level) {
    SmartDevice* device = findDeviceByName(name);
    if (!device) {
        return false;
    }

    auto* light = dynamic_cast<Light*>(device);
    if (!light) {
        return false;
    }

    try {
        light->setBrightness(level);
        return true;
    } catch (const InvalidInputException& ex) {
        std::cout << "Input error: " << ex.what() << std::endl;
    } catch (const InvalidDeviceStateException& ex) {
        std::cout << "State error: " << ex.what() << std::endl;
    }

    return false;
}

bool DeviceManager::setTvVolume(const std::string& name, int level) {
    SmartDevice* device = findDeviceByName(name);
    if (!device) {
        return false;
    }

    auto* tv = dynamic_cast<TV*>(device);
    if (!tv) {
        return false;
    }

    try {
        tv->setVolume(level);
        return true;
    } catch (const InvalidInputException& ex) {
        std::cout << "Input error: " << ex.what() << std::endl;
    } catch (const InvalidDeviceStateException& ex) {
        std::cout << "State error: " << ex.what() << std::endl;
    }

    return false;
}

bool DeviceManager::setTvChannel(const std::string& name, int channel) {
    SmartDevice* device = findDeviceByName(name);
    if (!device) {
        return false;
    }

    auto* tv = dynamic_cast<TV*>(device);
    if (!tv) {
        return false;
    }

    try {
        tv->setChannel(channel);
        return true;
    } catch (const InvalidInputException& ex) {
        std::cout << "Input error: " << ex.what() << std::endl;
    } catch (const InvalidDeviceStateException& ex) {
        std::cout << "State error: " << ex.what() << std::endl;
    }

    return false;
}

bool DeviceManager::connectComputerInternet(const std::string& name) {
    SmartDevice* device = findDeviceByName(name);
    if (!device) {
        return false;
    }

    auto* computer = dynamic_cast<Computer*>(device);
    if (!computer) {
        return false;
    }

    try {
        computer->connectInternet();
        return true;
    } catch (const InvalidInputException& ex) {
        std::cout << "Input error: " << ex.what() << std::endl;
    } catch (const InvalidDeviceStateException& ex) {
        std::cout << "State error: " << ex.what() << std::endl;
    }

    return false;
}
