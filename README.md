# Smart Home Automation System

## Overview
This project is a C++ smart home simulation built with object-oriented design. It models smart devices, manages them through a polymorphic container, and demonstrates interfaces, inheritance, runtime polymorphism, and exception handling.

Current architecture:

`main/menu -> RoomManager -> DeviceManager -> std::vector<std::unique_ptr<SmartDevice>>`

Implemented device types:
- `Light`
- `TV`
- `Computer`

## Design Summary
- `SmartDevice` is the abstract base class for all devices.
- `PowerInterface` is an interface-like class with pure virtual `turnOn()` and `turnOff()` methods.
- `Light`, `TV`, and `Computer` inherit from `SmartDevice` and implement `PowerInterface`.
- `DeviceManager` stores devices polymorphically and performs device-wide or device-specific operations.
- `RoomManager` provides room-level control on top of `DeviceManager`.
- Custom exceptions are used for invalid input and invalid device state.

## Features
- Runtime polymorphic status display through `SmartDevice` pointers.
- Batch power control through `PowerInterface`.
- Device-specific operations:
	- `Light`: brightness control
	- `TV`: volume and channel control
	- `Computer`: internet connection control
- Room-based listing and power control.
- Exception-safe manager wrappers that prevent the program from crashing.
- Interactive menu in `main.cpp` plus startup demonstration.

## Exception Rules
- `InvalidInputException`: thrown for invalid values such as brightness, volume, or channel input.
- `InvalidDeviceStateException`: thrown for invalid state changes such as powering on an already-on device or connecting internet while the computer is off.

## Files
- `SmartDevice.h` / `SmartDevice.cpp`: abstract base class
- `PowerInterface.h`: power-control interface
- `Light.h` / `Light.cpp`: light device
- `TV.h` / `TV.cpp`: TV device
- `Computer.h` / `Computer.cpp`: computer device
- `DeviceExceptions.h` / `DeviceExceptions.cpp`: custom exceptions
- `DeviceManager.h` / `DeviceManager.cpp`: polymorphic device manager
- `RoomManager.h` / `RoomManager.cpp`: room-level manager
- `main.cpp`: menu and demonstration

## Requirements Covered
- Multiple classes
- Inheritance
- Abstract base class
- Interface using pure virtual functions
- Virtual functions and runtime polymorphism
- Custom exceptions
- Proper encapsulation
- Separate header and implementation files

## Build and Run
```bash
g++ -std=c++17 -Wall -Wextra -pedantic *.cpp -o smart_home_app
./smart_home_app
```

Quick exit test:
```bash
printf "0\n" | ./smart_home_app
```
