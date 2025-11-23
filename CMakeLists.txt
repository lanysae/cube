cmake_minimum_required(VERSION 3.28.3)

project(cube)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES 0)

set(CUBE_SOURCES_PATH src)

set(CUBE_SOURCES
    ${CUBE_SOURCES_PATH}/main.cpp)

add_executable(cube ${CUBE_SOURCES})

target_compile_options(cube PRIVATE -Wall -Wextra -pedantic)
target_compile_options(cube PRIVATE -fdiagnostics-color -fansi-escape-codes)
