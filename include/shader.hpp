#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <glad/gl.h>
#include "math/matrix.hpp"
#include "utils/noncopyable.hpp"

class Shader : private NonCopyable {
public:
    Shader();
    ~Shader();

    explicit operator bool() const { return program != 0; }

    void bind() const;

    void setUniform(const std::string& name, const Matrix4f& m);

    static Shader loadFromFile(const std::string& vsFilename, const std::string& fsFilename);
    static Shader loadFromMemory(const std::string& vsSource, const std::string& fsSource);

private:
    GLuint program;

    Shader(GLuint program);

    GLint getUniformLocation(const std::string& name) const;
};

#endif
