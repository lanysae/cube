#include <cstdlib>
#include <imgui.h>
#include "window.hpp"

int main()
{
    Window window{ "Cube", 1280, 720 };
    if (!window)
        return EXIT_FAILURE;

    while (!window.shouldClose()) {
        window.beginFrame();

        ImGui::ShowDemoWindow();

        window.endFrame();
    }

    return EXIT_SUCCESS;
}
