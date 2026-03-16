#include "Computer.h"
#include "DeviceExceptions.h"
#include <iostream>

namespace {

// Print consistent power state message.
void printPowerStateMessage(const std::string& deviceName, bool isOn) {
    std::cout << deviceName << " is now " << (isOn ? "ON" : "OFF") << "." << std::endl;
}

}  // namespace

// Construct computer with initial network state.
Computer::Computer(const std::string& name, const std::string& location, bool internetConnected)
    : SmartDevice(name, location), isInternetConnected(internetConnected) {
}

// Turn device on through power interface.
void Computer::turnOn() {
    if (status) {
        throw InvalidDeviceStateException("Computer is already ON.");
    }
    status = true;
    printPowerStateMessage(name, status);
}

// Turn device off through power interface.
void Computer::turnOff() {
    if (!status) {
        throw InvalidDeviceStateException("Computer is already OFF.");
    }
    status = false;
    // Keep network state coherent with power state.
    isInternetConnected = false;
    printPowerStateMessage(name, status);
}

// Show current computer status fields.
void Computer::displayStatus() const {
    std::cout << "=== Computer Status ===" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Location: " << location << std::endl;
    std::cout << "Power: " << (status ? "ON" : "OFF") << std::endl;
    std::cout << "Internet: " << (isInternetConnected ? "Connected" : "Disconnected") << std::endl;
    std::cout << "=======================" << std::endl;
}

// Connect only when the device is powered on.
void Computer::connectInternet() {
    if (!status) {
        throw InvalidDeviceStateException("Computer must be ON before connecting to the internet.");
    }
    if (isInternetConnected) {
        throw InvalidDeviceStateException("Computer is already connected to the internet.");
    }

    isInternetConnected = true;
    std::cout << name << ": connected to the internet." << std::endl;
}

// Explicitly disconnect network.
void Computer::disconnectInternet() {
    if (!status) {
        throw InvalidDeviceStateException("Computer must be ON before disconnecting from the internet.");
    }
    if (!isInternetConnected) {
        throw InvalidDeviceStateException("Computer is not connected to the internet.");
    }

    isInternetConnected = false;
    std::cout << name << ": disconnected from the internet." << std::endl;
}

// Return current internet connection state.
bool Computer::isConnectedToInternet() const {
    return isInternetConnected;
}