#ifndef AC_H
#define AC_H

#include "PowerInterface.h"
#include "SmartDevice.h"
#include "TemperatureInterface.h"
#include <string>

class AC : public SmartDevice, public PowerInterface, public TemperatureInterface {
private:
    std::string mode;
    int temperature;

    void validateTemperature(int newTemperature) const;

public:
    AC(const std::string& name, const std::string& location);

    void turnOn() override;
    void turnOff() override;
    void displayStatus() const override;

    void increaseTemperature(int amount) override;
    void decreaseTemperature(int amount) override;
    int getTemperature() const override;

    void setCooling();
    void setHeating();
    std::string getMode() const;
};

#endif