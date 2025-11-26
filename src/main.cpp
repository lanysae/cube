#include <chrono>
#include <cstdlib>
#include <ratio>
#include <thread>
#include <imgui.h>
#include "window.hpp"

using FrameTime = std::chrono::duration<int, std::ratio<1, 30>>;

int main()
{
    Window window{ "Cube", 1280, 720 };
    if (!window)
        return EXIT_FAILURE;

    std::chrono::time_point nextFrame = std::chrono::system_clock::now() + FrameTime{ 1 };

    while (!window.shouldClose()) {
        window.beginFrame();

        ImGui::ShowDemoWindow();

        window.endFrame();

        std::this_thread::sleep_until(nextFrame);
        nextFrame += FrameTime{ 1 };
    }

    return EXIT_SUCCESS;
}
