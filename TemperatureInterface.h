#ifndef TEMPERATUREINTERFACE_H
#define TEMPERATUREINTERFACE_H

class TemperatureInterface {
public:
    virtual void increaseTemperature(int amount) = 0;
    virtual void decreaseTemperature(int amount) = 0;
    virtual int getTemperature() const = 0;
    virtual ~TemperatureInterface() = default;
};

#endif