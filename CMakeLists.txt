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

# cube

set(CUBE_SOURCES_PATH src)

set(CUBE_SOURCES
    ${CUBE_SOURCES_PATH}/main.cpp)

add_executable(cube ${CUBE_SOURCES})
target_link_libraries(cube PRIVATE
    glad
    glfw)

target_compile_options(cube PRIVATE -Wall -Wextra -pedantic)
target_compile_options(cube PRIVATE -fdiagnostics-color -fansi-escape-codes)
