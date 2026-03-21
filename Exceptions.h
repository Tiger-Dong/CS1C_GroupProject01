#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class AlreadyLockedException : public std::runtime_error {
public:
    explicit AlreadyLockedException(const std::string& message)
        : std::runtime_error(message) {}
};

class AlreadyUnlockedException : public std::runtime_error {
public:
    explicit AlreadyUnlockedException(const std::string& message)
        : std::runtime_error(message) {}
};

class CannotOpenLockedException : public std::runtime_error {
public:
    explicit CannotOpenLockedException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif