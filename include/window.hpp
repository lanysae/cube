#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include "math/vector.hpp"
#include "utils/noncopyable.hpp"

struct GLFWwindow;

class Window : private NonCopyable {
public:
    Window(const std::string& title, const Vector2i& size);
    ~Window();

    explicit operator bool() const { return window; }

    bool shouldClose() const;
    Vector2i getSize() const;

    void beginFrame();
    void endFrame();

private:
    GLFWwindow* window;
};

#endif
