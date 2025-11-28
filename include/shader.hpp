#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <glad/gl.h>
#include "utils/noncopyable.hpp"

class Shader : private NonCopyable {
public:
    Shader();
    ~Shader();

    bool loadFromFile(const std::string& vsFilename, const std::string& fsFilename);
    bool loadFromMemory(const std::string& vsSource, const std::string& fsSource);

private:
    GLuint program;
};

#endif
