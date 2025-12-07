#include "shader.hpp"
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <string>
#include <glad/gl.h>
#include <spdlog/spdlog.h>
#define STB_INCLUDE_IMPLEMENTATION
#include <stb_include.h>
#include "math/matrix.hpp"
#include "utils/assertion.hpp"

static char* stb_include_file_const(const char* filename, const char* inject, const char* path_to_includes, char error[256])
{
    return stb_include_file(const_cast<char*>(filename), const_cast<char*>(inject), const_cast<char*>(path_to_includes), error);
}

static std::optional<std::string> readFile(const std::filesystem::path& filename)
{
    const std::string parentPath = filename.parent_path().string();

    char error[256];
    char* result = stb_include_file_const(filename.string().c_str(), nullptr, parentPath.c_str(), error);
    if (!result) {
        spdlog::error("stb_include: {}", error);
        return std::nullopt;
    }

    const std::string content = result;
    std::free(result);

    return content;
}

static const char* getShaderTypeName(GLenum type)
{
    if (type == GL_VERTEX_SHADER)
        return "vertex";
    else if (type == GL_FRAGMENT_SHADER)
        return "fragment";

    return "<unknown>";
}

static GLuint compileShader(GLenum type, const char* source)
{
    Assert(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER);

    const GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus != GL_TRUE) {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        std::string infoLog(logLength, '\0');
        glGetShaderInfoLog(shader, logLength, nullptr, infoLog.data());

        spdlog::error("Unable to compile {} shader: {}", getShaderTypeName(type), infoLog);

        glDeleteShader(shader);

        return 0;
    }

    return shader;
}

static GLuint linkProgram(GLuint vs, GLuint fs)
{
    Assert(vs != 0 && fs != 0);

    const GLuint program = glCreateProgram();

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    glDetachShader(program, fs);
    glDetachShader(program, vs);

    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if (linkStatus != GL_TRUE) {
        GLint logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

        std::string infoLog(logLength, '\0');
        glGetProgramInfoLog(program, logLength, nullptr, infoLog.data());

        spdlog::error("Unable to link shaders: {}", infoLog);

        glDeleteProgram(program);

        return 0;
    }

    return program;
}

static GLuint compile(const char* vsSource, const char* fsSource)
{
    const GLuint vs = compileShader(GL_VERTEX_SHADER, vsSource);
    const GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsSource);

    const GLuint program = vs != 0 && fs != 0 ? linkProgram(vs, fs) : 0;

    glDeleteShader(fs);
    glDeleteShader(vs);

    return program;
}

Shader::Shader()
    : program{ 0 }
{
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

void Shader::bind() const
{
    Assert(program != 0);

    glUseProgram(program);
}

void Shader::setUniform(const std::string& name, const Matrix4f& m)
{
    Assert(program != 0);

    glProgramUniformMatrix4fv(program, getUniformLocation(name), 1, GL_FALSE, m.data());
}

Shader Shader::loadFromFile(const std::filesystem::path& vsFilename, const std::filesystem::path& fsFilename)
{
    const std::optional<std::string> vsSource = readFile(vsFilename);
    const std::optional<std::string> fsSource = readFile(fsFilename);
    if (!vsSource || !fsSource)
        return Shader{};

    return loadFromMemory(*vsSource, *fsSource);
}

Shader Shader::loadFromMemory(const std::string& vsSource, const std::string& fsSource)
{
    const GLuint program = compile(vsSource.c_str(), fsSource.c_str());

    return Shader{ program };
}

Shader::Shader(GLuint program)
    : program{ program }
{
}

GLint Shader::getUniformLocation(const std::string& name) const
{
    Assert(program != 0);

    const GLint location = glGetUniformLocation(program, name.c_str());
    if (location == -1)
        spdlog::warn("'{}' does not correspond to an active uniform variable", name);

    return location;
}
