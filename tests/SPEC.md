# Smart Home Device SPEC

## 1. Computer

### 1.1 Purpose
- Represent a power-controllable computer with internet connectivity state.

### 1.2 State
- `power`: `ON` or `OFF`
- `internet`: `Connected` or `Disconnected`
- `type`: `DeviceType::Computer`

### 1.3 Construction
- Given `(name, location, internetConnected)`:
    - `type` shall be `DeviceType::Computer`.
    - `internet` shall equal `internetConnected`.
    - `power` shall initialize to `OFF`.

### 1.4 Operations
- `turnOn()`
    - Precondition: current power is `OFF`.
    - Postcondition: power becomes `ON`.
    - Exception: throw `InvalidDeviceStateException` if already `ON`.

- `turnOff()`
    - Precondition: current power is `ON`.
    - Postcondition: power becomes `OFF`.
    - Postcondition: internet becomes `Disconnected`.
    - Exception: throw `InvalidDeviceStateException` if already `OFF`.

- `connectInternet()`
    - Precondition: power is `ON`.
    - Precondition: internet is currently `Disconnected`.
    - Postcondition: internet becomes `Connected`.
    - Exception: throw `InvalidDeviceStateException` if power is `OFF`.
    - Exception: throw `InvalidDeviceStateException` if already connected.

- `disconnectInternet()`
    - Precondition: power is `ON`.
    - Precondition: internet is currently `Connected`.
    - Postcondition: internet becomes `Disconnected`.
    - Exception: throw `InvalidDeviceStateException` if power is `OFF`.
    - Exception: throw `InvalidDeviceStateException` if already disconnected.

- `isConnectedToInternet()`
    - Returns the current internet state as a boolean.

### 1.5 Invariants
- Power and internet transitions must never silently ignore invalid state actions.
- Invalid state actions must throw `InvalidDeviceStateException`.

### 1.6 Test Mapping
- `tests/computer.test.cpp`

## 2. Light

### 2.1 Purpose
- Represent a power-controllable light with adjustable brightness.

### 2.2 State
- `power`: `ON` or `OFF`
- `brightness`: integer in range `[0, 100]`
- `type`: `DeviceType::Light`

### 2.3 Construction
- Given `(name, location, initialBrightness)`:
    - `type` shall be `DeviceType::Light`.
    - `power` shall initialize to `OFF`.
    - `brightness` shall be normalized to `[0, 100]`.

### 2.4 Operations
- `turnOn()`
    - Precondition: current power is `OFF`.
    - Postcondition: power becomes `ON`.
    - Exception: throw `InvalidDeviceStateException` if already `ON`.

- `turnOff()`
    - Precondition: current power is `ON`.
    - Postcondition: power becomes `OFF`.
    - Exception: throw `InvalidDeviceStateException` if already `OFF`.

- `setBrightness(level)`
    - Precondition: `0 <= level <= 100`.
    - Postcondition: brightness equals `level`.
    - Exception: throw `InvalidInputException` if level is outside `[0, 100]`.

- `getBrightness()`
    - Returns current brightness.

### 2.5 Invariants
- Brightness value must always remain in `[0, 100]`.
- Invalid input must throw `InvalidInputException`.

### 2.6 Test Mapping
- `tests/light.test.cpp`

## 3. TV

### 3.1 Purpose
- Represent a power-controllable TV with volume and channel controls.

### 3.2 State
- `power`: `ON` or `OFF`
- `volume`: integer in range `[0, 100]`
- `channel`: integer in range `[1, +inf)`
- `type`: `DeviceType::TV`

### 3.3 Construction
- Given `(name, location, initialVolume, initialChannel)`:
    - `type` shall be `DeviceType::TV`.
    - `power` shall initialize to `OFF`.
    - `volume` shall be normalized to `[0, 100]`.
    - `channel` shall be normalized to at least `1`.

### 3.4 Operations
- `turnOn()`
    - Precondition: current power is `OFF`.
    - Postcondition: power becomes `ON`.
    - Exception: throw `InvalidDeviceStateException` if already `ON`.

- `turnOff()`
    - Precondition: current power is `ON`.
    - Postcondition: power becomes `OFF`.
    - Exception: throw `InvalidDeviceStateException` if already `OFF`.

- `setVolume(level)`
    - Precondition: `0 <= level <= 100`.
    - Postcondition: volume equals `level`.
    - Exception: throw `InvalidInputException` if level is outside `[0, 100]`.

- `setChannel(channel)`
    - Precondition: `channel >= 1`.
    - Postcondition: channel equals input value.
    - Exception: throw `InvalidInputException` if channel is less than `1`.

- `getVolume()`
    - Returns current volume.

- `getChannel()`
    - Returns current channel.

### 3.5 Invariants
- Volume must always remain in `[0, 100]`.
- Channel must always be greater than or equal to `1`.
- Invalid state transitions must throw `InvalidDeviceStateException`.
- Invalid input values must throw `InvalidInputException`.

### 3.6 Test Mapping
- `tests/tv.test.cpp`