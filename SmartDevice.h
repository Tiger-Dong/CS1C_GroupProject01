#ifndef SMARTDEVICE_H
#define SMARTDEVICE_H

#include "DeviceType.h"
#include <string>

// Abstract base type for all smart-home devices.
class SmartDevice {
protected:
    // Basic identity fields shared by all devices.
    std::string name;
    std::string location;
    bool status;  // true = ON, false = OFF
    DeviceType type;

public:
    // Build a generic smart device with default OFF state.
    SmartDevice(const std::string& name, const std::string& location, DeviceType type);

    virtual ~SmartDevice();

    // Read-only identity/status accessors.
    std::string getName() const;

    std::string getLocation() const;

    bool getStatus() const;

    DeviceType getType() const;

    void printStatus() const;

    // Device-specific status view implemented by each derived type.
    virtual void displayStatus() const = 0;
};

#endif