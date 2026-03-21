#include "Door.h"

#include "Exceptions.h"
#include <iostream>

Door::Door(const std::string& name, const std::string& location)
    : SmartDevice(name, location, DeviceType::Door), openState(false), locked(true) {}

void Door::open() {
    openDoor();
}

void Door::close() {
    closeDoor();
}

void Door::openDoor() {
    if (locked) {
        throw CannotOpenLockedException("Cannot open a locked door.");
    }
    openState = true;
}

void Door::closeDoor() {
    openState = false;
}

void Door::lock() {
    if (locked) {
        throw AlreadyLockedException("Door is already locked.");
    }
    if (openState) {
        throw CannotOpenLockedException("Cannot lock an open door.");
    }
    locked = true;
}

void Door::unlock() {
    if (!locked) {
        throw AlreadyUnlockedException("Door is already unlocked.");
    }
    locked = false;
}

bool Door::isLocked() const {
    return locked;
}

bool Door::isOpen() const {
    return openState;
}

void Door::displayStatus() const {
    std::cout << "=== Door Status ===" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Location: " << location << std::endl;
    std::cout << "Open: " << (openState ? "Yes" : "No") << std::endl;
    std::cout << "Locked: " << (locked ? "Yes" : "No") << std::endl;
    std::cout << "===================" << std::endl;
}