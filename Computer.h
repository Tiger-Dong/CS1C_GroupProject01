#ifndef COMPUTER_H
#define COMPUTER_H

#include "DeviceType.h"
#include "SmartDevice.h"
#include "PowerInterface.h"
#include <string>

// Computer device with internet connectivity state.
class Computer : public SmartDevice, public PowerInterface {
private:
    // Tracks network connection status.
    bool isInternetConnected;

public:
    Computer(const std::string& name, const std::string& location, bool internetConnected = false);

    void turnOn() override;
    void turnOff() override;
    void displayStatus() const override;

    // Network controls for the computer.
    void connectInternet();
    void disconnectInternet();
    bool isConnectedToInternet() const;
};

#endif