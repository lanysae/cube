#ifndef MESH_HPP
#define MESH_HPP

#include <span>
#include <glad/gl.h>
#include "math/vector.hpp"
#include "utils/noncopyable.hpp"

class Mesh : private NonCopyable {
public:
    struct Vertex {
        Vector3f position;
        Vector3f color;
        Vector2f texCoords;
    };

    Mesh(std::span<const Vertex> vertices, std::span<const unsigned int> indices);
    ~Mesh();

    void draw() const;

private:
    GLuint vertexArray;
    GLuint vertexBuffer;
    GLuint indexBuffer;
    int count;
};

#endif
