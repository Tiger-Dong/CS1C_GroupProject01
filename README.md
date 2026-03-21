# Smart Home Automation System

## Overview
This project now follows the broader room-driven architecture used in the reference repository while preserving the stricter validation from the original local implementation.

Public manager and room APIs now use a single camelCase style, so room and device operations are exposed through calls such as `createRoom`, `addDeviceToRoom`, `turnOnDevice`, and `isDeviceLocked`.

Current architecture:

`main -> RoomManager -> Room -> DeviceManager -> SmartDevice hierarchy`

Implemented device types:
- `Light`
- `TV`
- `Computer`
- `AC`
- `Door`
- `Window`

## Design Summary
- `SmartDevice` is the abstract base class for all devices and now tracks `DeviceType` in addition to name, location, and power status.
- `PowerInterface`, `TemperatureInterface`, and `LockInterface` model capability-based behavior.
- `DeviceManager` no longer owns devices. It operates on borrowed `SmartDevice*` pointers and dispatches to the supported interface.
- `Room` owns devices polymorphically and represents the reference repository's room-centric design.
- `RoomManager` owns rooms and exposes room-level creation, listing, and device control operations.
- `DeviceFactory` centralizes room-aware device creation.
- Custom exceptions are used for invalid input, invalid state transitions, and lock-specific failures.
- A single camelCase naming convention is used across manager, room, and device APIs to reduce duplicate wrappers.

## What Was Kept From The Local Version
- `location` remains part of each device and is populated from the owning room name.
- Existing `Light`, `TV`, and `Computer` classes keep the stricter state checks already present locally.
- Manager APIs return `bool` for missing room/device cases, while invalid operations still throw meaningful exceptions.

## Build and Run
```bash
g++ -std=c++17 -Wall -Wextra -pedantic *.cpp -o smart_home_app
./smart_home_app
```

## Key Files
- `SmartDevice.h` / `SmartDevice.cpp`: abstract base class with `DeviceType`
- `DeviceType.h`: device kind enumeration
- `PowerInterface.h`: power-control interface
- `TemperatureInterface.h`: AC temperature interface
- `LockInterface.h`: door/window lock interface
- `Light.h` / `Light.cpp`: light device
- `TV.h` / `TV.cpp`: TV device
- `Computer.h` / `Computer.cpp`: computer device
- `AC.h` / `AC.cpp`: HVAC-style temperature device
- `Door.h` / `Door.cpp`: lockable door device
- `Window.h` / `Window.cpp`: lockable window device
- `DeviceFactory.h`: room-aware device creation
- `DeviceManager.h` / `DeviceManager.cpp`: capability dispatcher
- `Room.h` / `Room.cpp`: room-owned device container
- `RoomManager.h` / `RoomManager.cpp`: top-level room coordinator
- `DeviceExceptions.h` / `DeviceExceptions.cpp`: input/state exceptions
- `Exceptions.h`: lock-specific exceptions
- `main.cpp`: integration demo

Quick exit test:
```bash
printf "0\n" | ./smart_home_app
```
