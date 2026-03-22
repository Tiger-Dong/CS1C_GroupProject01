# Smart Home Automation System — Presentation Script

## Part 1: Project Overview

### 1.1 Assignment Objective
We were tasked to design and implement a **Smart Home Automation System** in C++ that demonstrates deep understanding of **Object-Oriented Programming (OOP)** principles. This includes:

- **Inheritance**: Building a device hierarchy where all smart devices inherit from a common abstract base.
- **Polymorphism**: Enabling devices to behave differently through virtual functions and interface implementation.
- **Interfaces (Multiple Inheritance)**: Modeling capabilities that devices may or may not support (power control, locking, temperature control).
- **Exception Handling**: Providing precise error semantics for invalid input and invalid state transitions.
- **Memory Management**: Using `std::unique_ptr` for safe ownership and RAII principles.

### 1.2 Architecture Overview

```
main (user interaction)
  ↓
RoomManager (top-level coordinator, owns all rooms)
  ↓
Room (room-centric design, owns all devices in that room)
  ↓
DeviceManager (capability dispatcher, operates on SmartDevice pointers)
  ↓
SmartDevice* (polymorphic pointer, actual device is one of TV, Light, Computer, AC, Door, Window)
```

Each layer is responsible for a specific concern:
- **RoomManager**: Create/list rooms, coordinate operations across rooms.
- **Room**: Own devices polymorphically, delegate operations to DeviceManager.
- **DeviceManager**: Cast SmartDevice* to capability interfaces and dispatch.
- **SmartDevice + Interfaces**: Enforce state invariants and input validation.

---

## Part 2: Core Architecture Design Rationale

### 2.1 Abstract Base Class: SmartDevice

```cpp
class SmartDevice {
protected:
    std::string name;
    std::string location;
    bool status;          // ON/OFF
    DeviceType type;      // Enumeration for device identity
public:
    virtual void displayStatus() const = 0;  // Pure virtual
    virtual ~SmartDevice() = default;
};
```

**Why this design?**
- **Identity Unification**: All devices share name, location, power status, and type. This centralizes common functionality.
- **Pure Virtual Method**: Forces derived classes to implement device-specific status display.
- **Polymorphic Container**: Enabled storage as `std::vector<std::unique_ptr<SmartDevice>>`, supporting heterogeneous device types.
- **Protected Members**: Allows subclasses to access identity fields directly, reducing getters and enabling efficient status checks.

### 2.2 Capability Interfaces: PowerInterface, LockInterface, TemperatureInterface

```cpp
class PowerInterface {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual ~PowerInterface() = default;
};

class LockInterface {
public:
    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual bool isLocked() const = 0;
    virtual ~LockInterface() = default;
};

class TemperatureInterface {
public:
    virtual void increaseTemperature(int amount) = 0;
    virtual void decreaseTemperature(int amount) = 0;
    virtual int getTemperature() const = 0;
    virtual ~TemperatureInterface() = default;
};
```

**Why this design?**
- **Separation of Concerns**: Each interface models a single capability, not a device type.
- **Flexible Composition**: Devices implement multiple interfaces as needed. Example: AC implements both PowerInterface and TemperatureInterface.
- **Runtime Capability Detection**: DeviceManager uses `dynamic_cast` to check if a device supports a capability before invoking it.
- **Follows Single Responsibility Principle**: Each interface has one reason to change.

Example device implementations:
- `Light`: Inherits from SmartDevice and implements PowerInterface.
- `Door`: Inherits from SmartDevice and implements LockInterface.
- `AC`: Inherits from SmartDevice and implements both PowerInterface and TemperatureInterface.

### 2.3 Concrete Device Classes: TV, Light, Computer

**TV**: Power-controllable device with volume and channel settings.
- Inherits: SmartDevice, PowerInterface
- State: volume ∈ [0, 100], channel ≥ 1
- Constructor normalizes invalid inputs (clamping and floor operations)

**Light**: Power-controllable device with adjustable brightness.
- Inherits: SmartDevice, PowerInterface
- State: brightness ∈ [0, 100]
- Constructor clamps brightness to valid range

**Computer**: Power-controllable device with internet connectivity control.
- Inherits: SmartDevice, PowerInterface
- State: isInternetConnected (boolean), requires power to be ON before connecting
- Constructor sets initial internet state, but power defaults to OFF

---

## Part 3: My Contribution — TV, Light, Computer, and Unit Tests

### 3.1 Why I Wrote It This Way

#### 3.1.1 Constructor Normalization and Validation

**TV Constructor:**
```cpp
TV::TV(const std::string& name, const std::string& location, 
        int initialVolume = 10, int initialChannel = 1)
    : SmartDevice(name, location, DeviceType::TV),
      volume(normalizeVolume(initialVolume)),
      channel(normalizeChannel(initialChannel)) {}

int normalizeVolume(int value) {
    return value < 0 ? 0 : (value > 100 ? 100 : value);
}

int normalizeChannel(int value) {
    return value < 1 ? 1 : value;
}
```

**Design Decision:**
- **Fail-Safe Construction**: Invalid inputs are silently normalized rather than rejecting construction. This ensures the object always enters a valid state.
- **Consistency**: The TV always has volume ∈ [0, 100] and channel ≥ 1, even if the user passes garbage.
- **User-Friendly**: Constructor accepts any value gracefully, matching real-world expectations (a TV should just "work" even if someone passes -50 as volume).

#### 3.1.2 Setter Validation with Exceptions

**Light Setter:**
```cpp
void Light::setBrightness(int brightnessLevel) {
    if (brightnessLevel < 0 || brightnessLevel > 100) {
        throw InvalidInputException("Brightness must be between 0 and 100.");
    }
    brightness = brightnessLevel;
}
```

**Design Decision:**
- **Contract Enforcement at Runtime**: Setters must validate because they represent explicit user intent. Unlike construction (which can normalize), setters should reject out-of-range values.
- **Exception-Based Error Handling**: Throwing exceptions makes errors impossible to ignore. Returning false or errno-style codes allow errors to be silently discarded.
- **Custom Exception Type**: Using `InvalidInputException` rather than `std::invalid_argument` documents our specific error semantics.

#### 3.1.3 Power State Machine with Strict Enforcement

**Light Power Transitions:**
```cpp
void Light::turnOn() {
    if (status) {
        throw InvalidDeviceStateException("Light is already ON.");
    }
    status = true;
    printPowerStateMessage(name, status);
}

void Light::turnOff() {
    if (!status) {
        throw InvalidDeviceStateException("Light is already OFF.");
    }
    status = false;
    printPowerStateMessage(name, status);
}
```

**Design Decision:**
- **Finite State Machine**: Power states are binary (ON/OFF). Transitions are only valid from OFF→ON or ON→OFF. Attempting duplicate transitions throws.
- **Fail-Fast Pattern**: Invalid state transitions are caught immediately, not silently ignored. This prevents inconsistency bugs that hide for days.
- **User Feedback**: Printing messages on successful transitions helps users understand state changes in the interactive menu.

#### 3.1.4 Computer's Internet-Power Coupling

**Computer's Connected-Without-Power Check:**
```cpp
void Computer::connectInternet() {
    if (!status) {  // Power is OFF
        throw InvalidDeviceStateException("Must turn on computer before connecting internet.");
    }
    if (isInternetConnected) {
        throw InvalidDeviceStateException("Already connected.");
    }
    isInternetConnected = true;
}

void Computer::turnOff() {
    if (!status) {
        throw InvalidDeviceStateException("Computer is already OFF.");
    }
    status = false;
    isInternetConnected = false;  // Automatically disconnect
}
```

**Design Decision:**
- **Semantic Coupling**: Internet connectivity requires power. This is a **domain invariant** that must be enforced in code, not documentatio.
- **State Reset on Power Down**: Turning off the computer automatically disconnects internet. This prevents orphaned state.
- **Clear Preconditions**: The `connectInternet()` method explicitly documents that power must be ON, enforceable at runtime.

### 3.2 Test-Driven Development (TDD) Methodology

#### 3.2.1 Why We Wrote Tests First

**TDD Workflow:**
1. **Write Specification** (`tests/SPEC.md`): Define exact behavior, preconditions, postconditions, and exception contracts.
2. **Write Test Cases** (`tests/light.test.cpp`, `tests/tv.test.cpp`, `tests/computer.test.cpp`): Capture the spec as executable assertions.
3. **Write Minimal Implementation** (`Light.h/.cpp`, `TV.h/.cpp`, `Computer.h/.cpp`): Only code needed to pass tests.
4. **Refactor**: Improve code quality while keeping tests green.
5. **Repeat**: Add new requirements by writing new tests.

**Benefits:**
- **Executable Documentation**: Tests are living documentation of expected behavior. They cannot become stale.
- **Regression Prevention**: Any accidental code change that breaks behavior is caught immediately.
- **Design Emerges Naturally**: Writing tests forces thinking about APIs and edge cases before implementation.
- **Confidence in Refactoring**: With comprehensive tests, we can refactor without fear.

#### 3.2.2 TV Test Cases: Constructor Normalization

```cpp
TEST_CASE("TV constructor normalizes initial values") {
    TV tv("Living TV", "Living Room", -5, 0);

    REQUIRE(tv.getVolume() == 0);       // -5 → 0 (minimum)
    REQUIRE(tv.getChannel() == 1);      // 0 → 1 (minimum)
    REQUIRE(tv.getStatus() == false);   // Default OFF
    REQUIRE(tv.getType() == DeviceType::TV);
}

TEST_CASE("TV setters reject invalid values") {
    TV tv("Living TV", "Living Room");

    REQUIRE_THROWS_AS(tv.setVolume(-1), InvalidInputException);
    REQUIRE_THROWS_AS(tv.setVolume(101), InvalidInputException);
    REQUIRE_THROWS_AS(tv.setChannel(0), InvalidInputException);
}
```

**TDD Insight:**
- **Normalization in Constructor, Validation in Setter**: This reflects real-world distinctions. Construction is forgiving; runtime setters are strict.
- **Exception Specificity**: We don't just test "throws", we test for the **specific exception type**. This ensures error handling is unambiguous.

#### 3.2.3 Light Test Cases: Brightness Clamping and Power State Machine

```cpp
TEST_CASE("Light constructor clamps brightness") {
    Light light("Main Light", "Bedroom", 150);
    REQUIRE(light.getBrightness() == 100);  // Clamped to maximum
}

TEST_CASE("Light power transitions enforce state rules") {
    Light light("Main Light", "Bedroom");

    // Cannot turn OFF before turning ON
    REQUIRE_THROWS_AS(light.turnOff(), InvalidDeviceStateException);

    light.turnOn();
    REQUIRE(light.getStatus() == true);
    
    // Cannot turn ON twice
    REQUIRE_THROWS_AS(light.turnOn(), InvalidDeviceStateException);

    light.turnOff();
    REQUIRE(light.getStatus() == false);
}
```

**TDD Insight:**
- **Boundary Testing**: We test off-by-one values (brightness = 150 → 100) to verify clamping logic.
- **State Transition Paths**: We test the full lifecycle (OFF→ON→OFF), not just individual operations.
- **Error Cases as First-Class Citizens**: Invalid transitions are tested as rigorously as valid ones.

#### 3.2.4 Computer Test Cases: Internet-Power Coupling

```cpp
TEST_CASE("Computer internet operations require power on") {
    Computer computer("Workstation", "Office");

    REQUIRE_THROWS_AS(computer.connectInternet(), InvalidDeviceStateException);
    REQUIRE_THROWS_AS(computer.disconnectInternet(), InvalidDeviceStateException);
}

TEST_CASE("Computer internet connect and disconnect flow") {
    Computer computer("Workstation", "Office");

    computer.turnOn();
    computer.connectInternet();
    REQUIRE(computer.isConnectedToInternet() == true);

    // Cannot connect twice
    REQUIRE_THROWS_AS(computer.connectInternet(), InvalidDeviceStateException);

    computer.disconnectInternet();
    REQUIRE(computer.isConnectedToInternet() == false);
}

TEST_CASE("Turning computer off resets internet state") {
    Computer computer("Workstation", "Office");

    computer.turnOn();
    computer.connectInternet();
    REQUIRE(computer.isConnectedToInternet() == true);

    computer.turnOff();
    REQUIRE(computer.getStatus() == false);
    REQUIRE(computer.isConnectedToInternet() == false);  // Automatically reset
}
```

**TDD Insight:**
- **Semantic Invariants as Tests**: The coupling between power and internet is captured in test form. If any refactoring breaks this invariant, tests fail immediately.
- **Full Workflow Testing**: We test the happy path (turn on → connect → disconnect → turn off) and also error paths.
- **State Consistency Checks**: Multiple assertions in one test verify that the object remains in a consistent state after each operation.

#### 3.2.5 Catch2 Testing Framework

We used **Catch2 v3** for its:
- **Expressive Assertions**: `REQUIRE()`, `REQUIRE_THROWS_AS()` read naturally.
- **Test Organization**: `TEST_CASE()` blocks are self-contained and easily parameterized.
- **Failure Diagnostics**: When a test fails, Catch2 prints which assertion failed and why.
- **Integration with CMake**: Tests are discovered automatically via `add_test()`.

---

## Part 4: Exception System Design

### 4.1 Exception Hierarchy

We defined two categories of domain-specific exceptions:

**Input Validation Exceptions:**
```cpp
class InvalidInputException : public std::runtime_error {
public:
    explicit InvalidInputException(const std::string& message);
};
```
Thrown when a setter receives a value outside its valid range (e.g., brightness = 150).

**State Transition Exceptions:**
```cpp
class InvalidDeviceStateException : public std::runtime_error {
public:
    explicit InvalidDeviceStateException(const std::string& message);
};
```
Thrown when an operation is not allowed in the current state (e.g., turnOn() when already ON).

**Lock-Specific Exceptions:**
```cpp
class AlreadyLockedException : public std::runtime_error { ... };
class AlreadyUnlockedException : public std::runtime_error { ... };
class CannotOpenLockedException : public std::runtime_error { ... };
```
Thrown for lock-related invariant violations (used by Door and Window classes).

### 4.2 Why This Exception Design?

1. **Semantic Clarity**: Catching `InvalidInputException` tells the user "you gave me bad data", while `InvalidDeviceStateException` says "you did something out of order".
2. **Specific Handling**: Different exception types can be handled with different recovery strategies.
3. **Inheritance from std::runtime_error**: Ensures compatibility with standard exception handling patterns.

---

## Part 5: Design Principles and Patterns Applied

### 5.1 SOLID Principles

**S (Single Responsibility)**
- `PowerInterface` is responsible only for power control.
- `Light` is responsible for its specific brightness logic.
- `DeviceManager` is responsible only for dispatching to appropriate interfaces.

**O (Open/Closed)**
- The system is open for extension (new device types like AC, Door, Window) without modifying existing code.
- `SmartDevice` is closed for modification; new devices inherit from it.

**L (Liskov Substitution)**
- Any `SmartDevice*` can be passed to `DeviceManager` safely.
- Any `PowerInterface*` can be used wherever power control is needed.

**I (Interface Segregation)**
- Devices implement only the interfaces they need.
- Light implements PowerInterface but not LockInterface (Light doesn't lock).
- Door implements LockInterface but not PowerInterface (Door has no electrical control).

**D (Dependency Inversion)**
- High-level code (DeviceManager, Room) depends on abstractions (SmartDevice, PowerInterface), not concrete classes.

### 5.2 Design Patterns

**Factory Pattern**
- `DeviceFactory` centralizes object creation, ensuring consistency.

**Strategy Pattern**
- Interfaces (PowerInterface, LockInterface, TemperatureInterface) represent different strategies for controlling devices.

**Template Method Pattern**
- `SmartDevice` provides common structure; derived classes override `displayStatus()`.

**Polymorphism Pattern**
- All devices are stored as `SmartDevice*` and behave correctly via virtual functions.

---

## Part 6: Test Coverage Summary

### 6.1 TV Test Suite (`tests/tv.test.cpp`)

| Test Case | Purpose |
|-----------|---------|
| Constructor normalization | Verify -5 → 0 (volume) and 0 → 1 (channel) |
| Setter validation | Ensure setVolume/setChannel reject out-of-range |
| Power transitions | Verify ON/OFF state machine |

### 6.2 Light Test Suite (`tests/light.test.cpp`)

| Test Case | Purpose |
|-----------|---------|
| Constructor clamping | Verify brightness 150 → 100 |
| Brightness validation | Ensure setBrightness rejects negative/excessive values |
| Power state machine | Verify strict ON/OFF transitions |

### 6.3 Computer Test Suite (`tests/computer.test.cpp`)

| Test Case | Purpose |
|-----------|---------|
| Internet state initialization | Verify initial state from constructor |
| Internet requires power | Ensure connectInternet throws if power OFF |
| Internet flow | Test full connect/disconnect lifecycle with repeated operation checks |
| Power off resets internet | Verify isInternetConnected = false when turning off |

### 6.4 Test Execution

Run all tests via CMake:
```bash
cd build
ctest --test-dir . --output-on-failure
```

Success output indicates all TV, Light, and Computer invariants are preserved.

---

## Part 7: Integration with Broader System

### 7.1 Room Ownership Model

Rooms own devices polymorphically:
```cpp
std::vector<std::unique_ptr<SmartDevice>> devices;
```

This ensures:
- Devices are destroyed when the room is destroyed (RAII).
- All devices, regardless of type, are managed uniformly.

### 7.2 DeviceManager Dispatch

DeviceManager operates on borrowed pointers:
```cpp
void DeviceManager::turnOn(SmartDevice* device) const {
    if (auto powerDevice = dynamic_cast<PowerInterface*>(device)) {
        powerDevice->turnOn();
    }
}
```

This approach:
- Avoids ownership overhead in DeviceManager.
- Checks capability at runtime (Door doesn't have turnOn).
- Throws meaningful exceptions for invalid operations.

### 7.3 Capability Scalability

New device types can be added without modifying existing code:
1. Define the new class (e.g., `Refrigerator`).
2. Inherit from `SmartDevice` and implement needed interfaces.
3. Add factory method to `DeviceFactory`.
4. Write unit tests in `tests/refrigerator.test.cpp`.

---

## Part 8: Why This Architecture?

### 8.1 Maintainability
- Clear separation of concerns makes code easy to understand.
- Changes to one device type don't affect others.

### 8.2 Testability
- Small methods are easy to test.
- Interfaces enable mocking if needed.
- Exception-based error handling is more testable than return codes.

### 8.3 Extensibility
- Adding new devices requires no changes to existing code.
- New capabilities (e.g., motion sensing) can be added as new interfaces.

### 8.4 Robustness
- TDD ensures invariants are captured and enforced.
- Exception handling makes errors explicit.
- Type system (DeviceType enum) prevents runtime misidentification.

---

## Part 9: Lessons Learned

### 9.1 Constructor vs. Setter Philosophy
- **Constructors are forgiving** (normalize inputs) because objects must enter a valid initial state.
- **Setters are strict** (throw on invalid input) because they represent explicit user intent.

### 9.2 The Power of Specification
- Writing `SPEC.md` before implementation prevented misunderstandings.
- Tests that map directly to spec items are easiest to maintain.

### 9.3 Exception Specificity
- Specific exception types (InvalidInputException vs. InvalidDeviceStateException) enable precise error recovery.
- Generic exceptions (std::runtime_error) make it hard for callers to distinguish error types.

### 9.4 State Machine Discipline
- Enforcing strict state transitions prevents subtle bugs.
- The Computer's internet-power coupling example shows how domain invariants must be encoded in the type system, not just documentation.

---

## Part 10: Conclusion

This Smart Home Automation System demonstrates:

1. **OOP Mastery**: Abstract base classes, interfaces, polymorphism, and inheritance work together seamlessly.
2. **TDD Discipline**: Tests serve as executable specifications, ensuring requirements are met and preventing regressions.
3. **Robust Design**: Exception handling, input validation, and state machine discipline make the system reliable.
4. **Professional Code**: Follows SOLID principles, uses design patterns appropriately, and is easily extended.

My responsibility was to implement **TV**, **Light**, and **Computer** classes with their unit tests. By adhering to TDD, I ensured each device:
- Normalizes constructor inputs gracefully.
- Validates setter inputs strictly and throws meaningful exceptions.
- Enforces state machine discipline (no duplicate power transitions).
- Couples semantically-related state (Computer's internet-power coupling).
- Is fully covered by executable tests that document expected behavior.

This foundation enabled the team to build a complete smart home system with confidence.
