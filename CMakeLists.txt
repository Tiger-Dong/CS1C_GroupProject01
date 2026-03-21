cmake_minimum_required(VERSION 3.10)
project(MyProject)

add_subdirectory(external/Catch2)

enable_testing()

add_subdirectory(tests)