#include "SmartDevice.h"

// Initialize shared identity and default power state.
SmartDevice::SmartDevice(const std::string& name, const std::string& location)
    : name(name), location(location), status(false) {}

SmartDevice::~SmartDevice() = default;

// Return device name.
std::string SmartDevice::getName() const {
    return name;
}

// Return device location.
std::string SmartDevice::getLocation() const {
    return location;
}

// Return current power status.
bool SmartDevice::getStatus() const {
    return status;
}