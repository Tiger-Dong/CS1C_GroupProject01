# Smart Home Module (PowerInterface + Light/TV/Computer)

## Module Overview
This module implements the power-device subsystem of a smart home system, including:
- Abstract base class: `SmartDevice`
- Interface: `PowerInterface`
- Concrete devices: `Light`, `TV`, `Computer`
- Custom exceptions: `InvalidInputException`, `InvalidDeviceStateException`

This module already demonstrates inheritance, polymorphism, interface usage, exception throwing/catching, and header/source separation.

## File Structure
- `SmartDevice.h` / `SmartDevice.cpp`: abstract device base type (name, location, power state, status display API)
- `PowerInterface.h`: power control interface (`turnOn()` / `turnOff()`)
- `Light.h` / `Light.cpp`: light device (brightness control)
- `TV.h` / `TV.cpp`: TV device (volume/channel control)
- `Computer.h` / `Computer.cpp`: computer device (network control)
- `DeviceExceptions.h` / `DeviceExceptions.cpp`: module exception types
- `main.cpp`: demo entry point (interface, polymorphism, exceptions)

## Module Interface Reference
### 1) SmartDevice (Abstract Base Class)
```cpp
class SmartDevice {
public:
    SmartDevice(const std::string& name, const std::string& location);
    virtual ~SmartDevice();

    std::string getName() const;
    std::string getLocation() const;
    bool getStatus() const;

    virtual void displayStatus() const = 0;
};
```
Purpose:
- Common parent type for polymorphic storage and access in `DeviceManager`.

### 2) PowerInterface (Interface)
```cpp
class PowerInterface {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual ~PowerInterface() = default;
};
```
Purpose:
- Unified power-control entry for batch on/off operations.

### 3) Light
```cpp
class Light : public SmartDevice, public PowerInterface {
public:
    Light(const std::string& name, const std::string& location, int initialBrightness = 50);

    void turnOn() override;
    void turnOff() override;
    void displayStatus() const override;

    void setBrightness(int brightnessLevel);   // [0, 100], throws on invalid input
    int getBrightness() const;
};
```

### 4) TV
```cpp
class TV : public SmartDevice, public PowerInterface {
public:
    TV(const std::string& name, const std::string& location, int initialVolume = 10, int initialChannel = 1);

    void turnOn() override;
    void turnOff() override;
    void displayStatus() const override;

    void setVolume(int volumeLevel);           // auto-clamped to [0, 100]
    void setChannel(int channelNumber);        // throws if < 1
    int getVolume() const;
    int getChannel() const;
};
```

### 5) Computer
```cpp
class Computer : public SmartDevice, public PowerInterface {
public:
    Computer(const std::string& name, const std::string& location, bool internetConnected = false);

    void turnOn() override;
    void turnOff() override;
    void displayStatus() const override;

    void connectInternet();                    // throws if device is OFF
    void disconnectInternet();
    bool isConnectedToInternet() const;
};
```

### 6) Exception Types
```cpp
class InvalidInputException : public std::runtime_error {};
class InvalidDeviceStateException : public std::runtime_error {};
```
Recommended catch pattern:
```cpp
try {
    // device operations
} catch (const InvalidInputException& ex) {
    // handle invalid input
} catch (const InvalidDeviceStateException& ex) {
    // handle invalid state
}
```

## Build and Run
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp SmartDevice.cpp Light.cpp TV.cpp Computer.cpp DeviceExceptions.cpp -o smart_home_app
./smart_home_app
```

## Integration Notes
- `DeviceManager` is recommended to store devices as: `std::vector<std::unique_ptr<SmartDevice>>`
- For unified status display, call: `SmartDevice* -> displayStatus()`
- For batch power control, call: `PowerInterface* -> turnOn()/turnOff()`
- Wrap potentially failing operations with `try/catch` to avoid program interruption
