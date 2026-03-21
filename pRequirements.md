# Project Requirements: Smart Home Automation System

## Assignment
Implement a Smart Home Automation System in C++ using OOP principles — inheritance, polymorphism, interfaces, and exceptions.

---

## Constraints

| Requirement                   | Met | How                                                                 |
|-------------------------------|-----|---------------------------------------------------------------------|
| ≥ 6 classes                   | ✅  | 14+ classes                                                         |
| ≥ 3 concrete derived classes  | ✅  | `TV`, `Light`, `Computer`, `AC`, `Door`, `Window`                   |
| ≥ 1 abstract base class       | ✅  | `SmartDevice` — pure virtual `displayStatus()`                      |
| ≥ 1 interface                 | ✅  | `PowerInterface`, `LockInterface`, `TemperatureInterface`           |
| ≥ 2 custom exception classes  | ✅  | `InvalidInputException`, `InvalidDeviceStateException`, `AlreadyLockedException`, `AlreadyUnlockedException`, `CannotOpenLockedException` |

---

## Class Structure

**Abstract base:** `SmartDevice` — stores `name`, `location`, `status`, `type`

**Interfaces:**
- `PowerInterface` → `turnOn()`, `turnOff()` — used by `TV`, `Light`, `Computer`, `AC`
- `LockInterface` → `lock()`, `unlock()`, `isLocked()` — used by `Door`, `Window`
- `TemperatureInterface` → temperature controls — used by `AC`

**Devices:**

| Class      | Interfaces                               | Key State                           |
|------------|------------------------------------------|-------------------------------------|
| `TV`       | `PowerInterface`                         | `volume [0,100]`, `channel [1,∞)`   |
| `Light`    | `PowerInterface`                         | `brightness [0,100]`                |
| `Computer` | `PowerInterface`                         | `isInternetConnected`               |
| `AC`       | `PowerInterface`, `TemperatureInterface` | `temperature`, `mode`               |
| `Door`     | `LockInterface`                          | `openState`, `locked`               |
| `Window`   | `LockInterface`                          | `openState`, `locked`               |

**Managers:**
- `DeviceManager` — operates on `SmartDevice*` via `dynamic_cast` to interfaces
- `Room` — owns devices as `unique_ptr<SmartDevice>`, delegates to `DeviceManager`
- `RoomManager` — top-level API: create rooms, add/remove/control devices

---

## Exceptions

| Exception                    | Thrown When                              |
|------------------------------|------------------------------------------|
| `InvalidInputException`      | Input value out of valid range           |
| `InvalidDeviceStateException`| Operation illegal in current state       |
| `AlreadyLockedException`     | `lock()` on already-locked device        |
| `AlreadyUnlockedException`   | `unlock()` on already-unlocked device    |
| `CannotOpenLockedException`  | Opening a locked door or window          |

---

## Unit Tests (my modules)

| Module     | Test File                    | Coverage                                                        |
|------------|------------------------------|-----------------------------------------------------------------|
| `TV`       | `tests/tv.test.cpp`          | Constructor normalization, setter validation, power transitions |
| `Light`    | `tests/light.test.cpp`       | Constructor clamping, brightness validation, power transitions  |
| `Computer` | `tests/computer.test.cpp`    | Internet requires power, connect/disconnect flow, turnOff resets internet |

Full method specs: `tests/SPEC.md`

---

## Current Summary

| Requirement | Goal | Files Involved (Complete?) | Status | Missing (if not met) |
|-------------|------|----------------------------|--------|----------------------|
| OOP smart-home architecture with inheritance, polymorphism, interfaces, and exceptions | Build a maintainable multi-device automation system with clear abstractions | `SmartDevice.h/.cpp`, `PowerInterface.h`, `LockInterface.h`, `TemperatureInterface.h`, `TV.h/.cpp`, `Light.h/.cpp`, `Computer.h/.cpp`, `AC.h/.cpp`, `Door.h/.cpp`, `Window.h/.cpp`, `DeviceManager.h/.cpp`, `Room.h/.cpp`, `RoomManager.h/.cpp`, `DeviceFactory.h`, `DeviceType.h`, `main.cpp` (Complete: Yes) | ✅ | None |
| Custom exception handling for invalid input/state/lock flows | Prevent invalid operations and provide explicit error semantics | `Exceptions.h`, `DeviceExceptions.h/.cpp`, device implementations that throw exceptions (Complete: Yes) | ✅ | None |
| Unit testing for assigned modules (`TV`, `Light`, `Computer`) | Verify constructor behavior, validation rules, and state transitions | `tests/tv.test.cpp`, `tests/light.test.cpp`, `tests/computer.test.cpp`, `tests/SPEC.md`, `tests/CMakeLists.txt` (Complete: Yes) | ✅ | None |
| Unit testing for all device modules (`AC`, `Door`, `Window`) | Reach broader regression coverage across all concrete devices | Existing project files present, but dedicated tests not listed in `tests/` (Complete: No) | ❌ | Add `tests/ac.test.cpp`, `tests/door.test.cpp`, `tests/window.test.cpp` and register them in `tests/CMakeLists.txt` |
