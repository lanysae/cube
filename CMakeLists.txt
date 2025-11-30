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

# ImGui

set(IMGUI_SOURCES_PATH deps/imgui)
set(IMGUI_HEADERS_PATH deps/imgui)

set(IMGUI_SOURCES
    ${IMGUI_SOURCES_PATH}/imgui.cpp
    ${IMGUI_SOURCES_PATH}/imgui_demo.cpp
    ${IMGUI_SOURCES_PATH}/imgui_draw.cpp
    ${IMGUI_SOURCES_PATH}/imgui_tables.cpp
    ${IMGUI_SOURCES_PATH}/imgui_widgets.cpp
    ${IMGUI_SOURCES_PATH}/backends/imgui_impl_glfw.cpp
    ${IMGUI_SOURCES_PATH}/backends/imgui_impl_opengl3.cpp)
set(IMGUI_HEADERS
    ${IMGUI_HEADERS_PATH}/imconfig.h
    ${IMGUI_HEADERS_PATH}/imgui.h
    ${IMGUI_HEADERS_PATH}/imgui_internal.h
    ${IMGUI_HEADERS_PATH}/imstb_rectpack.h
    ${IMGUI_HEADERS_PATH}/imstb_textedit.h
    ${IMGUI_HEADERS_PATH}/imstb_truetype.h
    ${IMGUI_HEADERS_PATH}/backends/imgui_impl_glfw.h
    ${IMGUI_HEADERS_PATH}/backends/imgui_impl_opengl3.h
    ${IMGUI_HEADERS_PATH}/backends/imgui_impl_opengl3_loader.h)

add_library(ImGui STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS})
target_include_directories(ImGui PUBLIC ${IMGUI_HEADERS_PATH})
target_link_libraries(ImGui PRIVATE glfw)

# spdlog

add_subdirectory(deps/spdlog)

# stb

set(STB_HEADERS_PATH deps/stb)

set(STB_HEADERS
    ${STB_HEADERS_PATH}/stb_include.h)

add_library(stb INTERFACE ${STB_HEADERS})
target_include_directories(stb INTERFACE ${STB_HEADERS_PATH})

# cube

set(CUBE_SOURCES_PATH src)
set(CUBE_HEADERS_PATH include)

set(CUBE_SOURCES
    ${CUBE_SOURCES_PATH}/main.cpp
    ${CUBE_SOURCES_PATH}/math/matrix.cpp
    ${CUBE_SOURCES_PATH}/mesh.cpp
    ${CUBE_SOURCES_PATH}/shader.cpp
    ${CUBE_SOURCES_PATH}/window.cpp)
set(CUBE_HEADERS
    ${CUBE_HEADERS_PATH}/math/math.hpp
    ${CUBE_HEADERS_PATH}/math/matrix.hpp
    ${CUBE_HEADERS_PATH}/math/vector.hpp
    ${CUBE_HEADERS_PATH}/mesh.hpp
    ${CUBE_HEADERS_PATH}/shader.hpp
    ${CUBE_HEADERS_PATH}/utils/assertion.hpp
    ${CUBE_HEADERS_PATH}/utils/noncopyable.hpp
    ${CUBE_HEADERS_PATH}/window.hpp)

add_executable(cube ${CUBE_SOURCES} ${CUBE_HEADERS})
target_include_directories(cube PRIVATE ${CUBE_HEADERS_PATH})
target_link_libraries(cube PRIVATE
    glad
    glfw
    ImGui
    spdlog::spdlog
    stb)

if (MSVC)
    target_compile_options(cube PRIVATE /W4)
else()
    target_compile_options(cube PRIVATE -Wall -Wextra -pedantic)

    if (CMAKE_GENERATOR STREQUAL "Ninja")
        target_compile_options(cube PRIVATE -fdiagnostics-color)
    endif()

    if (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(cube PRIVATE -fansi-escape-codes)
    endif()
endif()

if (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(cube PRIVATE $<$<CONFIG:Debug,RelWithDebInfo>:-gcodeview>)
    target_link_options(cube PRIVATE $<$<CONFIG:Debug,RelWithDebInfo>:-fuse-ld=lld;-Wl,/debug>)
endif()
