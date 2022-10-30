cmake_minimum_required(VERSION 3.18.0)

project(testTask-lib VERSION 1.0.0 LANGUAGES CXX)

include_directories("${CMAKE_SOURCE_DIR}/lib/Headers" "${PROJECT_NAME}/lib/Source")

add_library(${PROJECT_NAME}	
        Figure.cpp
        Headers/Figure.h
        Bitmap.cpp
        Headers/Bitmap.h
        Colors.cpp
        Headers/Colors.h
        )

target_include_directories(${PROJECT_NAME} PUBLIC Headers)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::gtest)