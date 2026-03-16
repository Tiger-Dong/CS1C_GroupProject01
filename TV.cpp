#include "TV.h"
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

// Construct TV with validated initial volume/channel.
TV::TV(const std::string& name, const std::string& location, int initialVolume, int initialChannel)
    : SmartDevice(name, location), volume(clampToPercent(initialVolume)), channel(initialChannel < 1 ? 1 : initialChannel) {
}

// Turn device on through power interface.
void TV::turnOn() {
    if (status) {
        throw InvalidDeviceStateException("TV is already ON.");
    }
    status = true;
    printPowerStateMessage(name, status);
}

// Turn device off through power interface.
void TV::turnOff() {
    if (!status) {
        throw InvalidDeviceStateException("TV is already OFF.");
    }
    status = false;
    printPowerStateMessage(name, status);
}

// Show current TV status fields.
void TV::displayStatus() const {
    std::cout << "=== TV Status ===" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Location: " << location << std::endl;
    std::cout << "Power: " << (status ? "ON" : "OFF") << std::endl;
    std::cout << "Volume (%): " << volume << std::endl;
    std::cout << "Channel: " << channel << std::endl;
    std::cout << "===============" << std::endl;
}

// Reject invalid volume values.
void TV::setVolume(int volumeLevel) {
    if (volumeLevel < 0 || volumeLevel > 100) {
        throw InvalidInputException("Volume must be between 0 and 100.");
    }
    volume = volumeLevel;

    std::cout << name << ": volume set to " << volume << "." << std::endl;
}

// Reject invalid channel values.
void TV::setChannel(int channelNumber) {
    if (channelNumber < 1) {
        throw InvalidInputException("Channel must be 1 or higher.");
    }

    channel = channelNumber;
    std::cout << name << ": channel set to " << channel << "." << std::endl;
}

// Return current volume.
int TV::getVolume() const {
    return volume;
}

// Return current channel.
int TV::getChannel() const {
    return channel;
}