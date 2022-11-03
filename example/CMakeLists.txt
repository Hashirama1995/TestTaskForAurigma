cmake_minimum_required(VERSION 3.0)

project(Example VERSION 1.0.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} DummyEye.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC testTask-lib)
