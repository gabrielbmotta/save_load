cmake_minimum_required(VERSION 3.15)
project(save_load)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_EXAMPLE_SL "Build example application" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(SOURCES
    save_load.cpp
    save_load.h)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

if(BUILD_EXAMPLE_SL)
    add_executable(${PROJECT_NAME}_ex example.cpp)
    target_link_libraries(${PROJECT_NAME}_ex ${PROJECT_NAME})
endif()

