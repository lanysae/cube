#include <chrono>
#include <cstdlib>
#include <ratio>
#include <thread>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "math/math.hpp"
#include "math/matrix.hpp"
#include "math/vector.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "window.hpp"

using FrameTime = std::chrono::duration<int, std::ratio<1, 30>>;

void render(const Vector2i& size, Shader& shader, const Mesh& mesh)
{
    ImGui::ShowDemoWindow();

    const float fovY = degToRad(50);
    const float aspect = size.x / static_cast<float>(size.y);
    const float zNear = 0.125f;
    const float zFar = 1024;
    shader.setUniform("projection", Matrix4f::perspective(fovY, aspect, zNear, zFar));

    const float angle = degToRad(90) * glfwGetTime();
    const Vector3f position{ 0, 0, -5 };
    shader.setUniform("model", Matrix4f::translate(position) * Matrix4f::rotateY(angle));

    shader.bind();
    mesh.draw();
}

int main()
{
    Window window{ "Cube", Vector2i{ 1280, 720 } };
    if (!window)
        return EXIT_FAILURE;

    Shader shader;
    const bool loaded = shader.loadFromFile("shaders/main.vs.glsl", "shaders/main.fs.glsl");
    if (!loaded)
        return EXIT_FAILURE;

    const Mesh::Vertex vertices[] = {
        // Front
        { .position = Vector3f{ -1, -1, 1 }, .color = Vector3f{ 1, 0, 0 } },
        { .position = Vector3f{ 1, -1, 1 }, .color = Vector3f{ 1, 0, 0 } },
        { .position = Vector3f{ 1, 1, 1 }, .color = Vector3f{ 1, 0, 0 } },
        { .position = Vector3f{ -1, 1, 1 }, .color = Vector3f{ 1, 0, 0 } },
        // Right
        { .position = Vector3f{ 1, -1, 1 }, .color = Vector3f{ 0, 1, 0 } },
        { .position = Vector3f{ 1, -1, -1 }, .color = Vector3f{ 0, 1, 0 } },
        { .position = Vector3f{ 1, 1, -1 }, .color = Vector3f{ 0, 1, 0 } },
        { .position = Vector3f{ 1, 1, 1 }, .color = Vector3f{ 0, 1, 0 } },
        // Back
        { .position = Vector3f{ 1, -1, -1 }, .color = Vector3f{ 0, 0, 1 } },
        { .position = Vector3f{ -1, -1, -1 }, .color = Vector3f{ 0, 0, 1 } },
        { .position = Vector3f{ -1, 1, -1 }, .color = Vector3f{ 0, 0, 1 } },
        { .position = Vector3f{ 1, 1, -1 }, .color = Vector3f{ 0, 0, 1 } },
        // Left
        { .position = Vector3f{ -1, -1, -1 }, .color = Vector3f{ 0, 1, 1 } },
        { .position = Vector3f{ -1, -1, 1 }, .color = Vector3f{ 0, 1, 1 } },
        { .position = Vector3f{ -1, 1, 1 }, .color = Vector3f{ 0, 1, 1 } },
        { .position = Vector3f{ -1, 1, -1 }, .color = Vector3f{ 0, 1, 1 } },
        // Top
        { .position = Vector3f{ -1, 1, 1 }, .color = Vector3f{ 1, 1, 0 } },
        { .position = Vector3f{ 1, 1, 1 }, .color = Vector3f{ 1, 1, 0 } },
        { .position = Vector3f{ 1, 1, -1 }, .color = Vector3f{ 1, 1, 0 } },
        { .position = Vector3f{ -1, 1, -1 }, .color = Vector3f{ 1, 1, 0 } },
        // Bottom
        { .position = Vector3f{ -1, -1, -1 }, .color = Vector3f{ 1, 0, 1 } },
        { .position = Vector3f{ 1, -1, -1 }, .color = Vector3f{ 1, 0, 1 } },
        { .position = Vector3f{ 1, -1, 1 }, .color = Vector3f{ 1, 0, 1 } },
        { .position = Vector3f{ -1, -1, 1 }, .color = Vector3f{ 1, 0, 1 } }
    };

    const unsigned int indices[] = {
        // Front
        0, 1, 2, 2, 3, 0,
        // Right
        4, 5, 6, 6, 7, 4,
        // Back
        8, 9, 10, 10, 11, 8,
        // Left
        12, 13, 14, 14, 15, 12,
        // Top
        16, 17, 18, 18, 19, 16,
        // Bottom
        20, 21, 22, 22, 23, 20
    };

    const Mesh mesh{ vertices, indices };

    std::chrono::time_point nextFrame = std::chrono::system_clock::now() + FrameTime{ 1 };

    while (!window.shouldClose()) {
        window.beginFrame();

        const Vector2i size = window.getSize();
        render(size, shader, mesh);

        window.endFrame();

        std::this_thread::sleep_until(nextFrame);
        nextFrame += FrameTime{ 1 };
    }

    return EXIT_SUCCESS;
}
