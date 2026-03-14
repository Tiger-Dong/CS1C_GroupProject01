#ifndef DEVICE_EXCEPTIONS_H
#define DEVICE_EXCEPTIONS_H

#include <stdexcept>
#include <string>

// Thrown when user input is outside valid ranges.
class InvalidInputException : public std::runtime_error {
public:
    explicit InvalidInputException(const std::string& message);
};

// Thrown when an operation is not allowed in current device state.
class InvalidDeviceStateException : public std::runtime_error {
public:
    explicit InvalidDeviceStateException(const std::string& message);
};

#endif