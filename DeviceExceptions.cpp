#include "DeviceExceptions.h"

// Forward message to std::runtime_error.
InvalidInputException::InvalidInputException(const std::string& message)
    : std::runtime_error(message) {}

// Forward message to std::runtime_error.
InvalidDeviceStateException::InvalidDeviceStateException(const std::string& message)
    : std::runtime_error(message) {}