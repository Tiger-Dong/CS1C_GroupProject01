#ifndef DOOR_H
#define DOOR_H

#include "LockInterface.h"
#include "SmartDevice.h"

class Door : public SmartDevice, public LockInterface {
private:
    bool openState;
    bool locked;

public:
    Door(const std::string& name, const std::string& location);

    void open();
    void close();
    void openDoor();
    void closeDoor();
    void lock() override;
    void unlock() override;
    bool isLocked() const override;

    bool isOpen() const;
    void displayStatus() const override;
};

#endif