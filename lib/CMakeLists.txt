cmake_minimum_required(VERSION 3.18.0)

project(testTask-lib VERSION 1.0.0 LANGUAGES CXX)

include_directories("${CMAKE_SOURCE_DIR}/lib/Headers" "${PROJECT_NAME}/lib/Figure_sources")

add_library(${PROJECT_NAME}	
        Headers/Figure.h
        Bitmap.cpp
        Headers/Bitmap.h
        Colors.cpp
        Headers/Colors.h
        UserInterface.cpp
        Headers/UserInterface.h
        Figure_sources/FigureContainer.cpp
        Figure_sources/FigurePoint.cpp
        Figure_sources/FigureLine.cpp
        Figure_sources/FigureBezierBurve3.cpp
        Figure_sources/FigureEllipse.cpp
        Figure_sources/FigureAbstractObject.cpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC Headers)
target_include_directories(${PROJECT_NAME} PUBLIC Figure_sources)
target_include_directories(${PROJECT_NAME} PUBLIC example)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::gtest)