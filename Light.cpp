#include "Light.h"
#include "DeviceExceptions.h"
#include <iostream>

namespace {

// Clamp a value to percentage range [0, 100].
int clampToPercent(int value) {
    if (value < 0) {
        return 0;
    }
    if (value > 100) {
        return 100;
    }
    return value;
}

// Print consistent power state message.
void printPowerStateMessage(const std::string& deviceName, bool isOn) {
    std::cout << deviceName << " is now " << (isOn ? "ON" : "OFF") << "." << std::endl;
}

}  // namespace

// Construct light with validated initial brightness.
Light::Light(const std::string& name, const std::string& location, int initialBrightness)
    : SmartDevice(name, location), brightness(clampToPercent(initialBrightness)) {
}

// Turn device on through power interface.
void Light::turnOn() {
    status = true;
    printPowerStateMessage(name, status);
}

// Turn device off through power interface.
void Light::turnOff() {
    status = false;
    printPowerStateMessage(name, status);
}

// Show current light status fields.
void Light::displayStatus() const {
    std::cout << "=== Light Status ===" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Location: " << location << std::endl;
    std::cout << "Power: " << (status ? "ON" : "OFF") << std::endl;
    std::cout << "Brightness (%): " << brightness << std::endl;
    std::cout << "====================" << std::endl;
}

// Validate brightness input before applying.
void Light::setBrightness(int brightnessLevel) {
    if (brightnessLevel < 0 || brightnessLevel > 100) {
        throw InvalidInputException("Brightness must be between 0 and 100.");
    }
    brightness = brightnessLevel;

    std::cout << name << ": brightness set to " << brightness << "." << std::endl;
}

// Return current brightness value.
int Light::getBrightness() const {
    return brightness;
}