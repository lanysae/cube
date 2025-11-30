#include <chrono>
#include <cstdlib>
#include <ratio>
#include <thread>
#include <imgui.h>
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
        { .position = Vector3f{ -0.5f, -0.5f, 0.f }, .color = Vector3f{ 1.f, 0.f, 0.f } },
        { .position = Vector3f{ 0.5f, -0.5f, 0.f }, .color = Vector3f{ 0.f, 1.f, 0.f } },
        { .position = Vector3f{ 0.f, 0.5f, 0.f }, .color = Vector3f{ 0.f, 0.f, 1.f } }
    };

    const unsigned int indices[] = { 0, 1, 2 };

    const Mesh mesh{ vertices, indices };

    std::chrono::time_point nextFrame = std::chrono::system_clock::now() + FrameTime{ 1 };

    while (!window.shouldClose()) {
        window.beginFrame();

        ImGui::ShowDemoWindow();

        shader.bind();
        mesh.draw();

        window.endFrame();

        std::this_thread::sleep_until(nextFrame);
        nextFrame += FrameTime{ 1 };
    }

    return EXIT_SUCCESS;
}
