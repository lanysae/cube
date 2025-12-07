#include "window.hpp"
#include <string>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glad/gl.h>
#include <imgui.h>
#include <spdlog/spdlog.h>
#include "math/vector.hpp"
#include "utils/assertion.hpp"

#ifndef NDEBUG
static void GLAPIENTRY debugMessageCallback(GLenum, GLenum type, GLuint, GLenum severity, GLsizei, const GLchar* message, const void*)
{
    if (severity == GL_DEBUG_SEVERITY_HIGH
        || severity == GL_DEBUG_SEVERITY_MEDIUM
        || severity == GL_DEBUG_SEVERITY_LOW) {
        if (type == GL_DEBUG_TYPE_ERROR)
            spdlog::error("{}", message);
        else
            spdlog::warn("{}", message);
    }
}
#endif

Window::Window(const std::string& title, const Vector2i& size)
{
    Assert(size.x > 0 && size.y > 0);

    spdlog::info("Creating window '{}' ({}x{})", title, size.x, size.y);

    glfwSetErrorCallback([](int, const char* description) {
        spdlog::error("GLFW error: {}", description);
    });

    if (!glfwInit())
        goto error_init;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#ifndef NDEBUG
    glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
    if (!window)
        goto error_window;

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        spdlog::error("Unable to load OpenGL");
        goto error_glad;
    }

#ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugMessageCallback, nullptr);
#endif

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

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

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::shouldClose() const
{
    Assert(window);

    return glfwWindowShouldClose(window);
}

Vector2i Window::getSize() const
{
    Assert(window);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    return Vector2i{ width, height };
}

void Window::beginFrame()
{
    Assert(window);

    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    const Vector2i size = getSize();
    glViewport(0, 0, size.x, size.y);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::endFrame()
{
    Assert(window);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}
