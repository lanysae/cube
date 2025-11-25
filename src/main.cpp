#include <cstdlib>
#include "window.hpp"

int main()
{
    Window window{ "Cube", 1280, 720 };
    if (!window)
        return EXIT_FAILURE;

    while (!window.shouldClose()) {
        window.beginFrame();
        window.endFrame();
    }

    return EXIT_SUCCESS;
}
