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

    bool loadFromFile(const std::string& vsFilename, const std::string& fsFilename);
    bool loadFromMemory(const std::string& vsSource, const std::string& fsSource);

    void bind() const;

    void setUniform(const std::string& name, const Matrix4f& m);

private:
    GLuint program;

    GLint getUniformLocation(const std::string& name) const;
};

#endif
