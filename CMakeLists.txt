cmake_minimum_required(VERSION 3.15)
project(save_load)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_EXAMPLES "Build example application" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(SOURCES
    save_load.cpp
    save_load.h)

add_library(${PROJECT_NAME} ${SOURCES})

if(BUILD_EXAMPLES)
    add_executable(${PROJECT_NAME}_ex main.cpp)
    target_link_libraries(${PROJECT_NAME}_ex ${PROJECT_NAME})
endif()

