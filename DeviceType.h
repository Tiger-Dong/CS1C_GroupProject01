#ifndef DEVICETYPE_H
#define DEVICETYPE_H

#include <string>

enum class DeviceType {
    NONE,
    Light,
    TV,
    Computer,
    AC,
    Door,
    Window,
};

inline std::string toString(DeviceType type) {
    switch (type) {
    case DeviceType::Light:
        return "Light";
    case DeviceType::TV:
        return "TV";
    case DeviceType::Computer:
        return "Computer";
    case DeviceType::AC:
        return "AC";
    case DeviceType::Door:
        return "Door";
    case DeviceType::Window:
        return "Window";
    default:
        return "Unknown";
    }
}

inline std::string to_string(DeviceType type) {
    return toString(type);
}

#endif