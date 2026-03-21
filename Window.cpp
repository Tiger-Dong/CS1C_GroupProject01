#include "Window.h"

#include "Exceptions.h"
#include <iostream>

Window::Window(const std::string& name, const std::string& location)
    : SmartDevice(name, location, DeviceType::Window), openState(false), locked(true) {}

void Window::open() {
    openWindow();
}

void Window::close() {
    closeWindow();
}

void Window::openWindow() {
    if (locked) {
        throw CannotOpenLockedException("Cannot open a locked window.");
    }
    openState = true;
}

void Window::closeWindow() {
    openState = false;
}

void Window::lock() {
    if (locked) {
        throw AlreadyLockedException("Window is already locked.");
    }
    if (openState) {
        throw CannotOpenLockedException("Cannot lock an open window.");
    }
    locked = true;
}

void Window::unlock() {
    if (!locked) {
        throw AlreadyUnlockedException("Window is already unlocked.");
    }
    locked = false;
}

bool Window::isLocked() const {
    return locked;
}

bool Window::isOpen() const {
    return openState;
}

void Window::displayStatus() const {
    std::cout << "=== Window Status ===" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Location: " << location << std::endl;
    std::cout << "Open: " << (openState ? "Yes" : "No") << std::endl;
    std::cout << "Locked: " << (locked ? "Yes" : "No") << std::endl;
    std::cout << "=====================" << std::endl;
}