#include "Computer.h"
#include "DeviceExceptions.h"
#include "Light.h"
#include "RoomManager.h"
#include "TV.h"
#include <iostream>
#include <limits>
#include <memory>
#include <string>

namespace {

void printMenu() {
    std::cout << "\n===== Smart Home Menu =====\n";
    std::cout << "1. List all devices\n";
    std::cout << "2. List devices in a room\n";
    std::cout << "3. Turn ON all devices\n";
    std::cout << "4. Turn OFF all devices\n";
    std::cout << "5. Turn ON a room\n";
    std::cout << "6. Turn OFF a room\n";
    std::cout << "7. Set light brightness\n";
    std::cout << "8. Set TV channel\n";
    std::cout << "9. Connect computer internet\n";
    std::cout << "10. Run exception demo\n";
    std::cout << "0. Exit\n";
    std::cout << "Select: ";
}

void runExceptionDemo() {
    std::cout << "\n=== Direct Exception Demo ===\n";
    try {
        Light demoLight("Demo Light", "Lab", 50);
        demoLight.setBrightness(200);
    } catch (const InvalidInputException& ex) {
        std::cout << "Caught InvalidInputException: " << ex.what() << std::endl;
    }

    try {
        Computer demoComputer("Demo PC", "Lab", false);
        demoComputer.disconnectInternet();
    } catch (const InvalidDeviceStateException& ex) {
        std::cout << "Caught InvalidDeviceStateException: " << ex.what() << std::endl;
    }
}

void bootstrapDevices(RoomManager& roomManager) {
    roomManager.addDevice(std::make_unique<Light>("Living Room Light", "Living Room", 70));
    roomManager.addDevice(std::make_unique<TV>("Bedroom TV", "Bedroom", 20, 5));
    roomManager.addDevice(std::make_unique<Computer>("Office PC", "Office", false));
    roomManager.addDevice(std::make_unique<Light>("Kitchen Light", "Kitchen", 40));
}

}  // namespace

int main() {
    RoomManager roomManager;
    bootstrapDevices(roomManager);

    std::cout << "=== Startup Demo (RoomManager -> DeviceManager -> SmartDevice) ===\n";
    roomManager.turnOnAll();
    roomManager.listAllDevices();
    roomManager.connectComputerInternet("Office PC");

    // Manager-level exception handling demo (returns false instead of crashing).
    if (!roomManager.setTvChannel("Bedroom TV", 0)) {
        std::cout << "Manager rejected invalid channel request.\n";
    }

    int choice = -1;
    while (choice != 0) {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Exiting menu.\n";
            break;
        }

        switch (choice) {
        case 1:
            roomManager.listAllDevices();
            break;
        case 2: {
            std::string room;
            std::cout << "Room name: ";
            std::cin >> room;
            roomManager.listDevicesInRoom(room);
            break;
        }
        case 3:
            roomManager.turnOnAll();
            break;
        case 4:
            roomManager.turnOffAll();
            break;
        case 5: {
            std::string room;
            std::cout << "Room name: ";
            std::cin >> room;
            roomManager.turnOnRoom(room);
            break;
        }
        case 6: {
            std::string room;
            std::cout << "Room name: ";
            std::cin >> room;
            roomManager.turnOffRoom(room);
            break;
        }
        case 7: {
            std::string lightName;
            int level = 0;
            std::cout << "Light name: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, lightName);
            std::cout << "Brightness [0-100]: ";
            std::cin >> level;
            if (!roomManager.setLightBrightness(lightName, level)) {
                std::cout << "Operation failed. Check name/type/value.\n";
            }
            break;
        }
        case 8: {
            std::string tvName;
            int channel = 0;
            std::cout << "TV name: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, tvName);
            std::cout << "Channel (>=1): ";
            std::cin >> channel;
            if (!roomManager.setTvChannel(tvName, channel)) {
                std::cout << "Operation failed. Check name/type/value.\n";
            }
            break;
        }
        case 9: {
            std::string pcName;
            std::cout << "Computer name: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, pcName);
            if (!roomManager.connectComputerInternet(pcName)) {
                std::cout << "Operation failed. Check name/type/state.\n";
            }
            break;
        }
        case 10:
            runExceptionDemo();
            break;
        case 0:
            std::cout << "Exiting Smart Home menu.\n";
            break;
        default:
            std::cout << "Unknown option. Try again.\n";
            break;
        }
    }

    return 0;
}