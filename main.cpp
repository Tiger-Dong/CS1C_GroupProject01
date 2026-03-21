#include "DeviceExceptions.h"
#include "Exceptions.h"
#include "RoomManager.h"

#include <iostream>
#include <stdexcept>

namespace {

void printSection(const std::string& title) {
    std::cout << "\n=== " << title << " ===" << std::endl;
}

void runDemo() {
    RoomManager roomManager;

    const int livingRoomId = roomManager.createRoom("Living Room");
    const int officeId = roomManager.createRoom("Office");

    roomManager.addDeviceToRoom(livingRoomId, DeviceType::Light, "Main Light");
    roomManager.addDeviceToRoom(livingRoomId, DeviceType::TV, "Family TV");
    roomManager.addDeviceToRoom(livingRoomId, DeviceType::Door, "Front Door");
    roomManager.addDeviceToRoom(officeId, DeviceType::Computer, "Workstation");
    roomManager.addDeviceToRoom(officeId, DeviceType::AC, "Office AC");
    roomManager.addDeviceToRoom(officeId, DeviceType::Window, "Office Window");

    printSection("Rooms");
    roomManager.listRooms();

    printSection("Initial Device State");
    roomManager.listAllDevices();

    printSection("Power On Supported Devices");
    roomManager.turnOnAll();
    roomManager.listAllDevices();

    printSection("Room-Specific Operations");
    roomManager.setLightBrightness(livingRoomId, 0, 75);
    roomManager.setTvChannel(livingRoomId, 1, 12);
    roomManager.connectComputerInternet(officeId, 0);
    roomManager.increaseDeviceTemperature(officeId, 1, 3);

    bool locked = false;
    roomManager.isDeviceLocked(livingRoomId, 2, locked);
    std::cout << "Front Door locked: " << (locked ? "Yes" : "No") << std::endl;
    roomManager.unlockDevice(livingRoomId, 2);
    roomManager.isDeviceLocked(livingRoomId, 2, locked);
    std::cout << "Front Door locked after unlock: " << (locked ? "Yes" : "No") << std::endl;

    printSection("Final Device State");
    roomManager.listAllDevices();

    printSection("Exception Demo");
    try {
        roomManager.setTvChannel(livingRoomId, 1, 0);
    } catch (const InvalidInputException& ex) {
        std::cout << "Caught InvalidInputException: " << ex.what() << std::endl;
    }

    try {
        roomManager.lockDevice(livingRoomId, 2);
        roomManager.lockDevice(livingRoomId, 2);
    } catch (const std::runtime_error& ex) {
        std::cout << "Caught runtime_error: " << ex.what() << std::endl;
    }
}

}  // namespace

int main() {
    try {
        runDemo();
    } catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}