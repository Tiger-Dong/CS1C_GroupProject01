#include "AC.h"

#include "DeviceExceptions.h"
#include <iostream>

AC::AC(const std::string& name, const std::string& location)
    : SmartDevice(name, location, DeviceType::AC), mode("Off"), temperature(72) {}

void AC::turnOn() {
    if (status) {
        throw InvalidDeviceStateException("AC is already ON.");
    }
    status = true;
    mode = "Cooling";
    std::cout << name << " is now ON." << std::endl;
}

void AC::turnOff() {
    if (!status) {
        throw InvalidDeviceStateException("AC is already OFF.");
    }
    status = false;
    mode = "Off";
    std::cout << name << " is now OFF." << std::endl;
}

void AC::displayStatus() const {
    std::cout << "=== AC Status ===" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Location: " << location << std::endl;
    std::cout << "Power: " << (status ? "ON" : "OFF") << std::endl;
    std::cout << "Mode: " << mode << std::endl;
    std::cout << "Temperature: " << temperature << std::endl;
    std::cout << "=================" << std::endl;
}

void AC::increaseTemperature(int amount) {
    if (!status) {
        throw InvalidDeviceStateException("Turn on the AC before changing temperature.");
    }
    validateTemperature(temperature + amount);
    temperature += amount;
}

void AC::decreaseTemperature(int amount) {
    if (!status) {
        throw InvalidDeviceStateException("Turn on the AC before changing temperature.");
    }
    validateTemperature(temperature - amount);
    temperature -= amount;
}

int AC::getTemperature() const {
    return temperature;
}

void AC::setCooling() {
    if (!status) {
        throw InvalidDeviceStateException("Turn on the AC before changing mode.");
    }
    mode = "Cooling";
}

void AC::setHeating() {
    if (!status) {
        throw InvalidDeviceStateException("Turn on the AC before changing mode.");
    }
    mode = "Heating";
}

std::string AC::getMode() const {
    return mode;
}

void AC::validateTemperature(int newTemperature) const {
    if (newTemperature < 60 || newTemperature > 90) {
        throw InvalidInputException("Temperature must be between 60 and 90.");
    }
}