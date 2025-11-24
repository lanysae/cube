#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include "utils/noncopyable.hpp"

struct GLFWwindow;

class Window : private NonCopyable {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    explicit operator bool() const { return window; }

    bool shouldClose() const;

    void beginFrame();
    void endFrame();

private:
    GLFWwindow* window;
};

#endif
