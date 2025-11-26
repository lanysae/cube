#include "window.hpp"
#include <string>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <spdlog/spdlog.h>
#include "utils/assertion.hpp"

Window::Window(const std::string& title, int width, int height)
{
    Assert(width > 0 && height > 0);

    spdlog::info("Creating window '{}' ({}x{})", title, width, height);

    glfwSetErrorCallback([](int, const char* description) {
        spdlog::error("GLFW error: {}", description);
    });

    if (!glfwInit())
        goto error_init;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window)
        goto error_window;

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        spdlog::error("Unable to load OpenGL");
        goto error_glad;
    }

    return;

error_glad:
    glfwDestroyWindow(window);
error_window:
    glfwTerminate();
error_init:
    window = nullptr;
}

Window::~Window()
{
    if (!window)
        return;

    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(window);
}

void Window::beginFrame()
{
    glfwPollEvents();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::endFrame()
{
    glfwSwapBuffers(window);
}
