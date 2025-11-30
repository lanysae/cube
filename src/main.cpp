#include <chrono>
#include <cstdlib>
#include <ratio>
#include <thread>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "math/matrix.hpp"
#include "math/vector.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "window.hpp"

using FrameTime = std::chrono::duration<int, std::ratio<1, 30>>;

int main()
{
    Window window{ "Cube", 1280, 720 };
    if (!window)
        return EXIT_FAILURE;

    Shader shader;
    const bool loaded = shader.loadFromFile("shaders/main.vs.glsl", "shaders/main.fs.glsl");
    if (!loaded)
        return EXIT_FAILURE;

    const Mesh::Vertex vertices[] = {
        { .position = Vector3f{ -0.5f, -0.25f, 0 }, .color = Vector3f{ 1, 0, 0 } },
        { .position = Vector3f{ 0.5f, -0.25f, 0 }, .color = Vector3f{ 0, 1, 0 } },
        { .position = Vector3f{ 0.0f, 0.5f, 0 }, .color = Vector3f{ 0, 0, 1 } }
    };

    const unsigned int indices[] = { 0, 1, 2 };

    const Mesh mesh{ vertices, indices };

    std::chrono::time_point nextFrame = std::chrono::system_clock::now() + FrameTime{ 1 };

    while (!window.shouldClose()) {
        window.beginFrame();

        ImGui::ShowDemoWindow();

        shader.setUniform("model", Matrix4f::rotateZ(glfwGetTime() * 0.5f));

        shader.bind();
        mesh.draw();

        window.endFrame();

        std::this_thread::sleep_until(nextFrame);
        nextFrame += FrameTime{ 1 };
    }

    return EXIT_SUCCESS;
}
