#ifndef DEVICEFACTORY_H
#define DEVICEFACTORY_H

#include "AC.h"
#include "Computer.h"
#include "DeviceType.h"
#include "Door.h"
#include "Light.h"
#include "SmartDevice.h"
#include "TV.h"
#include "Window.h"
#include <memory>
#include <string>

class DeviceFactory {
public:
    static std::unique_ptr<SmartDevice> createDevice(DeviceType type,
                                                     const std::string& name,
                                                     const std::string& location) {
        switch (type) {
        case DeviceType::Light:
            return std::make_unique<Light>(name, location);
        case DeviceType::TV:
            return std::make_unique<TV>(name, location);
        case DeviceType::Computer:
            return std::make_unique<Computer>(name, location);
        case DeviceType::AC:
            return std::make_unique<AC>(name, location);
        case DeviceType::Door:
            return std::make_unique<Door>(name, location);
        case DeviceType::Window:
            return std::make_unique<Window>(name, location);
        default:
            return nullptr;
        }
    }

};

#endif