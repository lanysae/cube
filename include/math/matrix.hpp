#ifndef MATH_MATRIX_HPP
#define MATH_MATRIX_HPP

#include <array>
#include "math/vector.hpp"

class Matrix4f {
public:
    std::array<float, 16> values;

    Matrix4f()
        : values{
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        }
    {
    }

    Matrix4f(
        float m11, float m21, float m31, float m41,
        float m12, float m22, float m32, float m42,
        float m13, float m23, float m33, float m43,
        float m14, float m24, float m34, float m44)
        : values{
            m11, m21, m31, m41,
            m12, m22, m32, m42,
            m13, m23, m33, m43,
            m14, m24, m34, m44
        }
    {
    }

    float* data() { return values.data(); }
    const float* data() const { return values.data(); }

    static Matrix4f translate(const Vector3f& v);
    static Matrix4f scale(const Vector3f& v);
    static Matrix4f scale(float s);
    static Matrix4f rotateX(float angle);
    static Matrix4f rotateY(float angle);
    static Matrix4f rotateZ(float angle);
    static Matrix4f rotate(const Vector3f& axis, float angle);
};

Matrix4f operator*(const Matrix4f& lhs, const Matrix4f& rhs);

Matrix4f transpose(const Matrix4f& m);

#endif
