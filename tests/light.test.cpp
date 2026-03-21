#include "Light.h"
#include "DeviceExceptions.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Light constructor clamps brightness") {
    Light light("Main Light", "Bedroom", 150);

    REQUIRE(light.getBrightness() == 100);
    REQUIRE(light.getStatus() == false);
    REQUIRE(light.getType() == DeviceType::Light);
}

TEST_CASE("Light brightness validation") {
    Light light("Main Light", "Bedroom", 50);

    light.setBrightness(0);
    REQUIRE(light.getBrightness() == 0);

    light.setBrightness(100);
    REQUIRE(light.getBrightness() == 100);

    REQUIRE_THROWS_AS(light.setBrightness(-1), InvalidInputException);
    REQUIRE_THROWS_AS(light.setBrightness(101), InvalidInputException);
}

TEST_CASE("Light power transitions enforce state rules") {
    Light light("Main Light", "Bedroom");

    REQUIRE_THROWS_AS(light.turnOff(), InvalidDeviceStateException);

    light.turnOn();
    REQUIRE(light.getStatus() == true);
    REQUIRE_THROWS_AS(light.turnOn(), InvalidDeviceStateException);

    light.turnOff();
    REQUIRE(light.getStatus() == false);
}
