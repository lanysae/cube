#include "math/matrix.hpp"
#include <cmath>
#include "math/vector.hpp"

Matrix4f Matrix4f::translate(const Vector3f& v)
{
    return Matrix4f{
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        v.x, v.y, v.z, 1
    };
}

Matrix4f Matrix4f::scale(const Vector3f& s)
{
    return Matrix4f{
        s.x, 0, 0, 0,
        0, s.y, 0, 0,
        0, 0, s.z, 0,
        0, 0, 0, 1
    };
}

Matrix4f Matrix4f::scale(float s)
{
    return Matrix4f{
        s, 0, 0, 0,
        0, s, 0, 0,
        0, 0, s, 0,
        0, 0, 0, 1
    };
}

Matrix4f Matrix4f::rotateX(float angle)
{
    const float c = std::cos(angle);
    const float s = std::sin(angle);

    return Matrix4f{
        1, 0, 0, 0,
        0, c, s, 0,
        0, -s, c, 0,
        0, 0, 0, 1
    };
}

Matrix4f Matrix4f::rotateY(float angle)
{
    const float c = std::cos(angle);
    const float s = std::sin(angle);

    return Matrix4f{
        c, 0, -s, 0,
        0, 1, 0, 0,
        s, 0, c, 0,
        0, 0, 0, 1
    };
}

Matrix4f Matrix4f::rotateZ(float angle)
{
    const float c = std::cos(angle);
    const float s = std::sin(angle);

    return Matrix4f{
        c, s, 0, 0,
        -s, c, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

Matrix4f Matrix4f::rotate(const Vector3f& axis, float angle)
{
    const Vector3f v = normalize(axis);
    const float c = std::cos(angle);
    const float s = std::sin(angle);
    const float omc = 1 - c;

    return Matrix4f{
        v.x * v.x * omc + c, v.x * v.y * omc + v.z * s, v.x * v.z * omc - v.y * s, 0,
        v.x * v.y * omc - v.z * s, v.y * v.y * omc + c, v.y * v.z * omc + v.x * s, 0,
        v.x * v.z * omc + v.y * s, v.y * v.z * omc - v.x * s, v.z * v.z * omc + c, 0,
        0, 0, 0, 1
    };
}

Matrix4f Matrix4f::frustum(float left, float right, float bottom, float top, float zNear, float zFar)
{
    return Matrix4f{
        2 * zNear / (right - left), 0, 0, 0,
        0, 2 * zNear / (top - bottom), 0, 0,
        (right + left) / (right - left), (top + bottom) / (top - bottom), -(zFar + zNear) / (zFar - zNear), -1,
        0, 0, -2 * zFar * zNear / (zFar - zNear), 0
    };
}

Matrix4f Matrix4f::perspective(float fovY, float aspect, float zNear, float zFar)
{
    const float top = zNear * std::tan(0.5f * fovY);
    const float right = aspect * top;

    return frustum(-right, right, -top, top, zNear, zFar);
}

Matrix4f operator*(const Matrix4f& lhs, const Matrix4f& rhs)
{
    Matrix4f result;

    for (int j = 0; j < 4; ++j)
        for (int i = 0; i < 4; ++i)
            result.values[4 * j + i] = lhs.values[i] * rhs.values[4 * j]
                                     + lhs.values[i + 4] * rhs.values[4 * j + 1]
                                     + lhs.values[i + 8] * rhs.values[4 * j + 2]
                                     + lhs.values[i + 12] * rhs.values[4 * j + 3];

    return result;
}

Matrix4f transpose(const Matrix4f& m)
{
    return Matrix4f{
        m.values[0], m.values[4], m.values[8], m.values[12],
        m.values[1], m.values[5], m.values[9], m.values[13],
        m.values[2], m.values[6], m.values[10], m.values[14],
        m.values[3], m.values[7], m.values[11], m.values[15]
    };
}
