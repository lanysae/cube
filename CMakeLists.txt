cmake_minimum_required(VERSION 3.28.3)

project(cube)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES 0)

# glad

set(GLAD_SOURCES_PATH deps/glad/src)
set(GLAD_HEADERS_PATH deps/glad/include)

set(GLAD_SOURCES
    ${GLAD_SOURCES_PATH}/gl.c)
set(GLAD_HEADERS
    ${GLAD_HEADERS_PATH}/glad/gl.h
    ${GLAD_HEADERS_PATH}/KHR/khrplatform.h)

add_library(glad STATIC ${GLAD_SOURCES} ${GLAD_HEADERS})
target_include_directories(glad PUBLIC ${GLAD_HEADERS_PATH})

# glfw

set(GLFW_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(deps/glfw)

# spdlog

add_subdirectory(deps/spdlog)

# cube

set(CUBE_SOURCES_PATH src)
set(CUBE_HEADERS_PATH include)

set(CUBE_SOURCES
    ${CUBE_SOURCES_PATH}/main.cpp
    ${CUBE_SOURCES_PATH}/window.cpp)
set(CUBE_HEADERS
    ${CUBE_HEADERS_PATH}/utils/noncopyable.hpp
    ${CUBE_HEADERS_PATH}/window.hpp)

add_executable(cube ${CUBE_SOURCES} ${CUBE_HEADERS})
target_include_directories(cube PRIVATE ${CUBE_HEADERS_PATH})
target_link_libraries(cube PRIVATE
    glad
    glfw
    spdlog)

target_compile_options(cube PRIVATE -Wall -Wextra -pedantic)
target_compile_options(cube PRIVATE -fdiagnostics-color -fansi-escape-codes)
