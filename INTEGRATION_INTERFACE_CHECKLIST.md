# Integration Interface Checklist

## 1. Ownership Model
- `RoomManager` owns `std::vector<Room>`.
- Each `Room` owns `std::vector<std::unique_ptr<SmartDevice>>`.
- `DeviceManager` does not own devices. It receives `SmartDevice*` and dispatches through capability interfaces.

## 2. Capability Layers
### A. Generic Device Layer (`SmartDevice*`)
- `getName()`
- `getLocation()`
- `getStatus()`
- `getType()`
- `printStatus()`
- `displayStatus()`

### B. Power Layer (`PowerInterface*`)
- `turnOn()`
- `turnOff()`

Supported by:
- `Light`
- `TV`
- `Computer`
- `AC`

### C. Temperature Layer (`TemperatureInterface*`)
- `increaseTemperature(int)`
- `decreaseTemperature(int)`
- `getTemperature()`

Supported by:
- `AC`

### D. Lock Layer (`LockInterface*`)
- `lock()`
- `unlock()`
- `isLocked()`

Supported by:
- `Door`
- `Window`

### E. Device-Specific Features
- `Light`: `setBrightness(int)` / `getBrightness()`
- `TV`: `setVolume(int)` / `setChannel(int)` / `getVolume()` / `getChannel()`
- `Computer`: `connectInternet()` / `disconnectInternet()` / `isConnectedToInternet()`
- `AC`: `setCooling()` / `setHeating()`
- `Door` and `Window`: `open()` / `close()`

## 3. Factory Integration
Recommended creation path:

```cpp
auto device = DeviceFactory::createDevice(type, deviceName, roomName);
```

This keeps room ownership centralized and ensures `location` is synchronized with the room name.

## 4. Exception Rules
This project may throw:
- `InvalidInputException`
- `InvalidDeviceStateException`
- `AlreadyLockedException`
- `AlreadyUnlockedException`
- `CannotOpenLockedException`

Recommended catch pattern:

```cpp
try {
    // room or device operation
} catch (const InvalidInputException& ex) {
    std::cout << "Input error: " << ex.what() << std::endl;
} catch (const InvalidDeviceStateException& ex) {
    std::cout << "State error: " << ex.what() << std::endl;
} catch (const std::runtime_error& ex) {
    std::cout << "Operation error: " << ex.what() << std::endl;
}
```

## 5. Compromise Decisions From The Merge
- Room ownership now matches the reference repository.
- Device `location` was kept from the local design because it makes status output clearer.
- DeviceManager follows the reference repository's capability-dispatch model.
- The stricter local validation for repeated power and network operations was preserved.
- The room-management layer and device-management APIs now use camelCase only to avoid duplicated method sets.

## 6. Pre-Integration Checklist
- [ ] Headers included: `SmartDevice.h`, `DeviceType.h`, `PowerInterface.h`, `TemperatureInterface.h`, `LockInterface.h`
- [ ] Rooms own devices polymorphically
- [ ] DeviceManager operates on borrowed `SmartDevice*`
- [ ] Device creation goes through `DeviceFactory`
- [ ] Invalid input/state is handled with `try/catch`
- [ ] Lock-capable devices use `LockInterface`
- [ ] Invalid input/state cases are covered (e.g., channel < 1, connect internet while OFF)
