add_executable(device_unit_tests
	hello_world.test.cpp
	tv.test.cpp
	light.test.cpp
	computer.test.cpp
	../SmartDevice.cpp
	../DeviceExceptions.cpp
	../TV.cpp
	../Light.cpp
	../Computer.cpp
)

target_include_directories(device_unit_tests PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(device_unit_tests PRIVATE Catch2::Catch2WithMain)

add_test(NAME device_unit_tests COMMAND device_unit_tests)