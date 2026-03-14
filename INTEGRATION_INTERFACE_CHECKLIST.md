# Integration Interface Checklist (for DeviceManager / RoomManager)

## 1. Capabilities You Can Call Directly
### A. Generic Device Layer (`SmartDevice*`)
- `getName()`: read device name
- `getLocation()`: read device location
- `getStatus()`: read power status (`true/false`)
- `displayStatus()`: polymorphic status display

Use cases:
- `DeviceManager::listAllDevices()`
- `RoomManager::listDevicesInRoom(roomName)`

### B. Generic Power Layer (`PowerInterface*`)
- `turnOn()`: power on
- `turnOff()`: power off

Use cases:
- `DeviceManager::turnOnAll()`
- `RoomManager::turnOffRoom(roomName)`

### C. Device-Specific Features (downcast as needed)
- `Light`: `setBrightness(int)` / `getBrightness()`
- `TV`: `setVolume(int)` / `setChannel(int)` / `getVolume()` / `getChannel()`
- `Computer`: `connectInternet()` / `disconnectInternet()` / `isConnectedToInternet()`

## 2. Recommended Data Structure
```cpp
// Inside DeviceManager
std::vector<std::unique_ptr<SmartDevice>> devices;
```

### Polymorphic status display
```cpp
for (const auto& device : devices) {
    device->displayStatus();
}
```

### Batch power control (interface-driven)
```cpp
for (const auto& device : devices) {
    if (auto* power = dynamic_cast<PowerInterface*>(device.get())) {
        power->turnOn();
    }
}
```

## 3. Exception Integration Rules
This module may throw:
- `InvalidInputException`
- `InvalidDeviceStateException`

Recommended manager-level handling:
```cpp
try {
    // call device operation
} catch (const InvalidInputException& ex) {
    std::cout << "Input error: " << ex.what() << std::endl;
} catch (const InvalidDeviceStateException& ex) {
    std::cout << "State error: " << ex.what() << std::endl;
}
```

## 4. Suggested Manager Wrapper Functions
- `bool setLightBrightness(const std::string& name, int level)`
- `bool setTvVolume(const std::string& name, int level)`
- `bool setTvChannel(const std::string& name, int channel)`
- `bool connectComputerInternet(const std::string& name)`

Suggested return behavior:
- `true`: operation succeeded
- `false`: device not found or type mismatch
- Invalid input/state: use exceptions to distinguish specific error causes

## 5. RoomManager Integration Notes
- Use `getLocation()` for room-based filtering
- Apply batch `turnOn/turnOff` to devices in a room
- Use `displayStatus()` for room-level status output to avoid duplicate formatting logic

## 6. Pre-Integration Checklist
- [ ] Headers included: `SmartDevice.h`, `PowerInterface.h`, `Light.h`, `TV.h`, `Computer.h`, `DeviceExceptions.h`
- [ ] Manager stores devices in a polymorphic `SmartDevice` container
- [ ] Power operations are called through `PowerInterface`
- [ ] `dynamic_cast` is used for device-specific features
- [ ] Exceptions are handled with `try/catch` to prevent crashes
- [ ] Invalid input/state cases are covered (e.g., channel < 1, connect internet while OFF)
