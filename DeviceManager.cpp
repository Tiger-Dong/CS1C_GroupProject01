#include "DeviceManager.h"

#include "Computer.h"
#include "LockInterface.h"
#include "Light.h"
#include "PowerInterface.h"
#include "TemperatureInterface.h"
#include "TV.h"
#include "DeviceExceptions.h"

namespace {

void validateDevicePointer(const SmartDevice* device) {
    if (!device) {
        throw InvalidDeviceStateException("Device pointer is null.");
    }
}

}  // namespace

void DeviceManager::turnOn(SmartDevice* device) const {
    validateDevicePointer(device);
    auto* power = dynamic_cast<PowerInterface*>(device);
    if (!power) {
        throw InvalidDeviceStateException("Device does not support power control.");
    }
    power->turnOn();
}

void DeviceManager::turnOff(SmartDevice* device) const {
    validateDevicePointer(device);
    auto* power = dynamic_cast<PowerInterface*>(device);
    if (!power) {
        throw InvalidDeviceStateException("Device does not support power control.");
    }
    power->turnOff();
}

void DeviceManager::increaseTemperature(SmartDevice* device, int amount) const {
    validateDevicePointer(device);
    auto* temperature = dynamic_cast<TemperatureInterface*>(device);
    if (!temperature) {
        throw InvalidDeviceStateException("Device does not support temperature control.");
    }
    temperature->increaseTemperature(amount);
}

void DeviceManager::decreaseTemperature(SmartDevice* device, int amount) const {
    validateDevicePointer(device);
    auto* temperature = dynamic_cast<TemperatureInterface*>(device);
    if (!temperature) {
        throw InvalidDeviceStateException("Device does not support temperature control.");
    }
    temperature->decreaseTemperature(amount);
}

int DeviceManager::getTemperature(SmartDevice* device) const {
    validateDevicePointer(device);
    auto* temperature = dynamic_cast<TemperatureInterface*>(device);
    if (!temperature) {
        throw InvalidDeviceStateException("Device does not support temperature control.");
    }
    return temperature->getTemperature();
}

void DeviceManager::lock(SmartDevice* device) const {
    validateDevicePointer(device);
    auto* lockable = dynamic_cast<LockInterface*>(device);
    if (!lockable) {
        throw InvalidDeviceStateException("Device does not support lock control.");
    }
    lockable->lock();
}

void DeviceManager::unlock(SmartDevice* device) const {
    validateDevicePointer(device);
    auto* lockable = dynamic_cast<LockInterface*>(device);
    if (!lockable) {
        throw InvalidDeviceStateException("Device does not support lock control.");
    }
    lockable->unlock();
}

bool DeviceManager::isLocked(SmartDevice* device) const {
    validateDevicePointer(device);
    auto* lockable = dynamic_cast<LockInterface*>(device);
    if (!lockable) {
        throw InvalidDeviceStateException("Device does not support lock control.");
    }
    return lockable->isLocked();
}

void DeviceManager::setLightBrightness(SmartDevice* device, int level) const {
    validateDevicePointer(device);
    auto* light = dynamic_cast<Light*>(device);
    if (!light) {
        throw InvalidDeviceStateException("Device is not a light.");
    }
    light->setBrightness(level);
}

void DeviceManager::setTvVolume(SmartDevice* device, int level) const {
    validateDevicePointer(device);
    auto* tv = dynamic_cast<TV*>(device);
    if (!tv) {
        throw InvalidDeviceStateException("Device is not a TV.");
    }
    tv->setVolume(level);
}

void DeviceManager::setTvChannel(SmartDevice* device, int channel) const {
    validateDevicePointer(device);
    auto* tv = dynamic_cast<TV*>(device);
    if (!tv) {
        throw InvalidDeviceStateException("Device is not a TV.");
    }
    tv->setChannel(channel);
}

void DeviceManager::connectComputerInternet(SmartDevice* device) const {
    validateDevicePointer(device);
    auto* computer = dynamic_cast<Computer*>(device);
    if (!computer) {
        throw InvalidDeviceStateException("Device is not a computer.");
    }
    computer->connectInternet();
}
