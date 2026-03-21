#include "Computer.h"
#include "DeviceExceptions.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Computer starts with configured internet state") {
    Computer computer("Workstation", "Office", true);

    REQUIRE(computer.isConnectedToInternet() == true);
    REQUIRE(computer.getStatus() == false);
    REQUIRE(computer.getType() == DeviceType::Computer);
}

TEST_CASE("Computer internet operations require power on") {
    Computer computer("Workstation", "Office");

    REQUIRE_THROWS_AS(computer.connectInternet(), InvalidDeviceStateException);
    REQUIRE_THROWS_AS(computer.disconnectInternet(), InvalidDeviceStateException);
}

TEST_CASE("Computer internet connect and disconnect flow") {
    Computer computer("Workstation", "Office");

    computer.turnOn();
    computer.connectInternet();
    REQUIRE(computer.isConnectedToInternet() == true);

    REQUIRE_THROWS_AS(computer.connectInternet(), InvalidDeviceStateException);

    computer.disconnectInternet();
    REQUIRE(computer.isConnectedToInternet() == false);

    REQUIRE_THROWS_AS(computer.disconnectInternet(), InvalidDeviceStateException);
}

TEST_CASE("Turning computer off resets internet state") {
    Computer computer("Workstation", "Office");

    computer.turnOn();
    computer.connectInternet();
    REQUIRE(computer.isConnectedToInternet() == true);

    computer.turnOff();
    REQUIRE(computer.getStatus() == false);
    REQUIRE(computer.isConnectedToInternet() == false);
}
