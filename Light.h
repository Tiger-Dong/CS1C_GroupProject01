#ifndef LIGHT_H
#define LIGHT_H

#include "SmartDevice.h"
#include "PowerInterface.h"
#include <string>

// Light device with adjustable brightness.
class Light : public SmartDevice, public PowerInterface {
private:
    // Brightness percentage in [0, 100].
    int brightness;

public:
    Light(const std::string& name, const std::string& location, int initialBrightness = 50);

    void turnOn() override;
    void turnOff() override;
    void displayStatus() const override;

    // Update brightness with range validation.
    void setBrightness(int brightnessLevel);
    // Read current brightness.
    int getBrightness() const;
};

#endif