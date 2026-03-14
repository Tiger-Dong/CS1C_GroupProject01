#ifndef POWERINTERFACE_H
#define POWERINTERFACE_H

// Common power-control behavior shared by switchable devices.
class PowerInterface {
public:
    // Power on the device.
    virtual void turnOn() = 0;
    // Power off the device.
    virtual void turnOff() = 0;
    virtual ~PowerInterface() = default;
};

#endif