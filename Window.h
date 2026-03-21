#ifndef WINDOW_H
#define WINDOW_H

#include "LockInterface.h"
#include "SmartDevice.h"

class Window : public SmartDevice, public LockInterface {
private:
    bool openState;
    bool locked;

public:
    Window(const std::string& name, const std::string& location);

    void open();
    void close();
    void openWindow();
    void closeWindow();
    void lock() override;
    void unlock() override;
    bool isLocked() const override;

    bool isOpen() const;
    void displayStatus() const override;
};

#endif