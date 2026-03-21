#include "RoomManager.h"

#include <iostream>

namespace {

Room* findRoomById(std::vector<Room>& rooms, int roomId) {
    for (Room& room : rooms) {
        if (room.getRoomId() == roomId) {
            return &room;
        }
    }
    return nullptr;
}

const Room* findRoomById(const std::vector<Room>& rooms, int roomId) {
    for (const Room& room : rooms) {
        if (room.getRoomId() == roomId) {
            return &room;
        }
    }
    return nullptr;
}

}  // namespace

int RoomManager::createRoom(const std::string& roomName) {
    rooms.emplace_back(roomName);
    return rooms.back().getRoomId();
}

Room* RoomManager::getRoom(int roomId) {
    return findRoomById(rooms, roomId);
}

const Room* RoomManager::getRoom(int roomId) const {
    return findRoomById(rooms, roomId);
}

bool RoomManager::removeRoom(int roomId) {
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
        if (it->getRoomId() == roomId) {
            rooms.erase(it);
            return true;
        }
    }
    return false;
}

bool RoomManager::addDeviceToRoom(int roomId, DeviceType type, const std::string& deviceName) {
    Room* room = getRoom(roomId);
    if (!room) {
        return false;
    }
    return room->addDeviceToRoom(type, deviceName);
}

bool RoomManager::removeDeviceFromRoom(int roomId, int deviceId) {
    Room* room = getRoom(roomId);
    if (!room) {
        return false;
    }
    return room->removeDevice(deviceId);
}

void RoomManager::listRooms() const {
    if (rooms.empty()) {
        std::cout << "No rooms created." << std::endl;
        return;
    }

    for (const Room& room : rooms) {
        std::cout << "Room [" << room.getRoomId() << "] " << room.getName() << std::endl;
    }
}

void RoomManager::listAllDevices() const {
    if (rooms.empty()) {
        std::cout << "No rooms created." << std::endl;
        return;
    }

    for (const Room& room : rooms) {
        std::cout << "\nRoom [" << room.getRoomId() << "] " << room.getName() << std::endl;
        room.listDevices();
    }
}

void RoomManager::listDevicesInRoom(int roomId) const {
    const Room* room = getRoom(roomId);
    if (!room) {
        std::cout << "Invalid room id: " << roomId << std::endl;
        return;
    }
    std::cout << "Room [" << room->getRoomId() << "] " << room->getName() << std::endl;
    room->listDevices();
}

void RoomManager::turnOnAll() {
    for (Room& room : rooms) {
        room.turnOnAllDevices();
    }
}

void RoomManager::turnOffAll() {
    for (Room& room : rooms) {
        room.turnOffAllDevices();
    }
}

bool RoomManager::turnOnRoom(int roomId) {
    Room* room = getRoom(roomId);
    if (!room) {
        return false;
    }
    room->turnOnAllDevices();
    return true;
}

bool RoomManager::turnOffRoom(int roomId) {
    Room* room = getRoom(roomId);
    if (!room) {
        return false;
    }
    room->turnOffAllDevices();
    return true;
}

bool RoomManager::turnOnDevice(int roomId, int deviceId) {
    Room* room = getRoom(roomId);
    if (!room || !room->getDevice(deviceId)) {
        return false;
    }
    room->turnOnDevice(deviceId);
    return true;
}

bool RoomManager::turnOffDevice(int roomId, int deviceId) {
    Room* room = getRoom(roomId);
    if (!room || !room->getDevice(deviceId)) {
        return false;
    }
    room->turnOffDevice(deviceId);
    return true;
}

bool RoomManager::increaseDeviceTemperature(int roomId, int deviceId, int amount) {
    Room* room = getRoom(roomId);
    if (!room || !room->getDevice(deviceId)) {
        return false;
    }
    room->increaseDeviceTemperature(deviceId, amount);
    return true;
}

bool RoomManager::decreaseDeviceTemperature(int roomId, int deviceId, int amount) {
    Room* room = getRoom(roomId);
    if (!room || !room->getDevice(deviceId)) {
        return false;
    }
    room->decreaseDeviceTemperature(deviceId, amount);
    return true;
}

bool RoomManager::lockDevice(int roomId, int deviceId) {
    Room* room = getRoom(roomId);
    if (!room || !room->getDevice(deviceId)) {
        return false;
    }
    room->lockDevice(deviceId);
    return true;
}

bool RoomManager::unlockDevice(int roomId, int deviceId) {
    Room* room = getRoom(roomId);
    if (!room || !room->getDevice(deviceId)) {
        return false;
    }
    room->unlockDevice(deviceId);
    return true;
}

bool RoomManager::isDeviceLocked(int roomId, int deviceId, bool& locked) const {
    const Room* room = getRoom(roomId);
    if (!room || !room->getDevice(deviceId)) {
        return false;
    }
    locked = room->isDeviceLocked(deviceId);
    return true;
}

bool RoomManager::setLightBrightness(int roomId, int deviceId, int level) {
    Room* room = getRoom(roomId);
    if (!room || !room->getDevice(deviceId)) {
        return false;
    }
    room->setLightBrightness(deviceId, level);
    return true;
}

bool RoomManager::setTvVolume(int roomId, int deviceId, int level) {
    Room* room = getRoom(roomId);
    if (!room || !room->getDevice(deviceId)) {
        return false;
    }
    room->setTvVolume(deviceId, level);
    return true;
}

bool RoomManager::setTvChannel(int roomId, int deviceId, int channel) {
    Room* room = getRoom(roomId);
    if (!room || !room->getDevice(deviceId)) {
        return false;
    }
    room->setTvChannel(deviceId, channel);
    return true;
}

bool RoomManager::connectComputerInternet(int roomId, int deviceId) {
    Room* room = getRoom(roomId);
    if (!room || !room->getDevice(deviceId)) {
        return false;
    }
    room->connectComputerInternet(deviceId);
    return true;
}
