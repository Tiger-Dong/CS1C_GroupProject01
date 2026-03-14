#ifndef TV_H
#define TV_H

#include "SmartDevice.h"
#include "PowerInterface.h"
#include <string>

// TV device with volume and channel controls.
class TV : public SmartDevice, public PowerInterface {
private:
    // Volume percentage in [0, 100].
    int volume;
    // Current channel number, minimum 1.
    int channel;

public:
    TV(const std::string& name, const std::string& location, int initialVolume = 10, int initialChannel = 1);

    void turnOn() override;
    void turnOff() override;
    void displayStatus() const override;

    // Setters/getters for TV-specific properties.
    void setVolume(int volumeLevel);
    void setChannel(int channelNumber);
    int getVolume() const;
    int getChannel() const;
};

#endif