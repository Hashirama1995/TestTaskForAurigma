cmake_minimum_required(VERSION 3.0)

project(Tests VERSION 1.0.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} tests.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC testTask-lib)

include(GoogleTest)

gtest_discover_tests(${PROJECT_NAME})