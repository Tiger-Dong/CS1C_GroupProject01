#include "Light.h"
#include "TV.h"
#include "Computer.h"
#include "DeviceExceptions.h"
#include <iostream>
#include <vector>

int main() {
    // Create concrete devices managed through shared interfaces.
    Light light("Living Room Light", "Living Room", 70);
    TV tv("Bedroom TV", "Bedroom", 20, 5);
    Computer pc("Office PC", "Office", false);

    // Separate views: one for power control, one for generic status display.
    std::vector<PowerInterface*> powerDevices = {&light, &tv, &pc};
    std::vector<SmartDevice*> allDevices = {&light, &tv, &pc};

    // Interface polymorphism: power on all devices through PowerInterface.
    for (PowerInterface* device : powerDevices) {
        device->turnOn();
    }

    // Runtime polymorphism: display device-specific status through SmartDevice.
    std::cout << "\n=== Polymorphic Device Status ===\n";
    for (SmartDevice* device : allDevices) {
        device->displayStatus();
    }

    pc.connectInternet();

    std::cout << "\n=== Exception Demo ===\n";
    // Invalid channel should raise input exception.
    try {
        tv.setChannel(0);
    } catch (const InvalidInputException& ex) {
        std::cout << "Caught InvalidInputException: " << ex.what() << std::endl;
    }

    // Connecting while OFF should raise device-state exception.
    try {
        Computer officeBackup("Backup PC", "Office", false);
        officeBackup.connectInternet();
    } catch (const InvalidDeviceStateException& ex) {
        std::cout << "Caught InvalidDeviceStateException: " << ex.what() << std::endl;
    }

    return 0;
}