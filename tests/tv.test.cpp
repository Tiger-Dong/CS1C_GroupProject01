#include "TV.h"
#include "DeviceExceptions.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("TV constructor normalizes initial values") {
    TV tv("Living TV", "Living Room", -5, 0);

    REQUIRE(tv.getVolume() == 0);
    REQUIRE(tv.getChannel() == 1);
    REQUIRE(tv.getStatus() == false);
    REQUIRE(tv.getType() == DeviceType::TV);
}

TEST_CASE("TV setters accept valid values") {
    TV tv("Living TV", "Living Room", 10, 2);

    tv.setVolume(80);
    tv.setChannel(15);

    REQUIRE(tv.getVolume() == 80);
    REQUIRE(tv.getChannel() == 15);
}

TEST_CASE("TV setters reject invalid values") {
    TV tv("Living TV", "Living Room");

    REQUIRE_THROWS_AS(tv.setVolume(-1), InvalidInputException);
    REQUIRE_THROWS_AS(tv.setVolume(101), InvalidInputException);
    REQUIRE_THROWS_AS(tv.setChannel(0), InvalidInputException);
}

TEST_CASE("TV power transitions enforce state rules") {
    TV tv("Living TV", "Living Room");

    REQUIRE_THROWS_AS(tv.turnOff(), InvalidDeviceStateException);

    tv.turnOn();
    REQUIRE(tv.getStatus() == true);
    REQUIRE_THROWS_AS(tv.turnOn(), InvalidDeviceStateException);

    tv.turnOff();
    REQUIRE(tv.getStatus() == false);
}