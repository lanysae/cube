#include "mesh.hpp"
#include <cstddef>
#include <span>
#include <glad/gl.h>
#include "math/vector.hpp"

Mesh::Mesh(std::span<const Vertex> vertices, std::span<const unsigned int> indices)
{
    glCreateVertexArrays(1, &vertexArray);

    glCreateBuffers(1, &vertexBuffer);
    glNamedBufferStorage(vertexBuffer, vertices.size_bytes(), vertices.data(), 0);
    glVertexArrayVertexBuffer(vertexArray, 0, vertexBuffer, 0, sizeof(Vertex));

    glEnableVertexArrayAttrib(vertexArray, 0);
    glVertexArrayAttribFormat(vertexArray, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
    glVertexArrayAttribBinding(vertexArray, 0, 0);

    glEnableVertexArrayAttrib(vertexArray, 1);
    glVertexArrayAttribFormat(vertexArray, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, color));
    glVertexArrayAttribBinding(vertexArray, 1, 0);

    glCreateBuffers(1, &indexBuffer);
    glNamedBufferStorage(indexBuffer, indices.size_bytes(), indices.data(), 0);
    glVertexArrayElementBuffer(vertexArray, indexBuffer);

    count = indices.size();
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &indexBuffer);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vertexArray);
}

void Mesh::draw() const
{
    glBindVertexArray(vertexArray);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, static_cast<const GLvoid*>(0));
}
