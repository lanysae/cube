#ifndef MATH_VECTOR_HPP
#define MATH_VECTOR_HPP

#include <cmath>
#include <concepts>
#include <type_traits>

template <typename T>
class Vector2 {
public:
    T x;
    T y;

    Vector2()
        : x{ 0 }
        , y{ 0 }
    {
    }

    explicit Vector2(T value)
        : x{ value }
        , y{ value }
    {
    }

    Vector2(T x, T y)
        : x{ x }
        , y{ y }
    {
    }

    template <typename U>
    explicit Vector2(const Vector2<U>& v)
        : x{ static_cast<T>(v.x) }
        , y{ static_cast<T>(v.y) }
    {
    }

    Vector2<T>& operator+=(const Vector2<T>& rhs)
    {
        x += rhs.x;
        y += rhs.y;

        return *this;
    }

    Vector2<T>& operator-=(const Vector2<T>& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;

        return *this;
    }

    Vector2<T>& operator*=(const Vector2<T>& rhs)
    {
        x *= rhs.x;
        y *= rhs.y;

        return *this;
    }

    template <typename U>
    Vector2<T>& operator*=(U rhs)
    {
        x *= rhs;
        y *= rhs;

        return *this;
    }

    Vector2<T>& operator/=(const Vector2<T>& rhs)
    {
        x /= rhs.x;
        y /= rhs.y;

        return *this;
    }

    template <typename U>
    Vector2<T>& operator/=(U rhs)
    {
        x /= rhs;
        y /= rhs;

        return *this;
    }

    auto operator<=>(const Vector2<T>&) const = default;
};

template <typename T>
inline Vector2<T> operator-(const Vector2<T>& rhs)
{
    return Vector2<T>{ -rhs.x, -rhs.y };
}

template <typename T>
inline Vector2<T> operator+(Vector2<T> lhs, const Vector2<T>& rhs)
{
    return lhs += rhs;
}

template <typename T>
inline Vector2<T> operator-(Vector2<T> lhs, const Vector2<T>& rhs)
{
    return lhs -= rhs;
}

template <typename T>
inline Vector2<T> operator*(Vector2<T> lhs, const Vector2<T>& rhs)
{
    return lhs *= rhs;
}

template <typename T, typename U>
inline Vector2<T> operator*(Vector2<T> lhs, U rhs)
{
    return lhs *= rhs;
}

template <typename T, typename U>
inline Vector2<T> operator*(U lhs, Vector2<T> rhs)
{
    return rhs *= lhs;
}

template <typename T>
inline Vector2<T> operator/(Vector2<T> lhs, const Vector2<T>& rhs)
{
    return lhs /= rhs;
}

template <typename T, typename U>
inline Vector2<T> operator/(Vector2<T> lhs, U rhs)
{
    return lhs /= rhs;
}

template <typename T>
inline T dot(const Vector2<T>& u, const Vector2<T>& v)
{
    return u.x * v.x + u.y * v.y;
}

template <typename T>
inline T lengthSquared(const Vector2<T>& v)
{
    return v.x * v.x + v.y * v.y;
}

template <typename T, typename Float = std::conditional_t<std::is_floating_point_v<T>, T, float>>
inline Float length(const Vector2<T>& v)
{
    const T x = lengthSquared(v);

    return std::sqrt(static_cast<Float>(x));
}

template <typename T>
inline T distanceSquared(const Vector2<T>& u, const Vector2<T>& v)
{
    return lengthSquared(u - v);
}

template <typename T, typename Float = std::conditional_t<std::is_floating_point_v<T>, T, float>>
inline Float distance(const Vector2<T>& u, const Vector2<T>& v)
{
    const T x = distanceSquared(u, v);

    return std::sqrt(static_cast<Float>(x));
}

template <typename T>
requires std::floating_point<T>
inline Vector2<T> normalize(const Vector2<T>& v)
{
    return v / length(v);
}

template <typename T>
class Vector3 {
public:
    T x;
    T y;
    T z;

    Vector3()
        : x{ 0 }
        , y{ 0 }
        , z{ 0 }
    {
    }

    explicit Vector3(T value)
        : x{ value }
        , y{ value }
        , z{ value }
    {
    }

    Vector3(T x, T y, T z)
        : x{ x }
        , y{ y }
        , z{ z }
    {
    }

    template <typename U>
    explicit Vector3(const Vector3<U>& v)
        : x{ static_cast<T>(v.x) }
        , y{ static_cast<T>(v.y) }
        , z{ static_cast<T>(v.z) }
    {
    }

    Vector3<T>& operator+=(const Vector3<T>& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;

        return *this;
    }

    Vector3<T>& operator-=(const Vector3<T>& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;

        return *this;
    }

    Vector3<T>& operator*=(const Vector3<T>& rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;

        return *this;
    }

    template <typename U>
    Vector3<T>& operator*=(U rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;

        return *this;
    }

    Vector3<T>& operator/=(const Vector3<T>& rhs)
    {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;

        return *this;
    }

    template <typename U>
    Vector3<T>& operator/=(U rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;

        return *this;
    }

    auto operator<=>(const Vector3<T>&) const = default;
};

template <typename T>
inline Vector3<T> operator-(const Vector3<T>& rhs)
{
    return Vector3<T>{ -rhs.x, -rhs.y, -rhs.z };
}

template <typename T>
inline Vector3<T> operator+(Vector3<T> lhs, const Vector3<T>& rhs)
{
    return lhs += rhs;
}

template <typename T>
inline Vector3<T> operator-(Vector3<T> lhs, const Vector3<T>& rhs)
{
    return lhs -= rhs;
}

template <typename T>
inline Vector3<T> operator*(Vector3<T> lhs, const Vector3<T>& rhs)
{
    return lhs *= rhs;
}

template <typename T, typename U>
inline Vector3<T> operator*(Vector3<T> lhs, U rhs)
{
    return lhs *= rhs;
}

template <typename T, typename U>
inline Vector3<T> operator*(U lhs, Vector3<T> rhs)
{
    return rhs *= lhs;
}

template <typename T>
inline Vector3<T> operator/(Vector3<T> lhs, const Vector3<T>& rhs)
{
    return lhs /= rhs;
}

template <typename T, typename U>
inline Vector3<T> operator/(Vector3<T> lhs, U rhs)
{
    return lhs /= rhs;
}

template <typename T>
inline T dot(const Vector3<T>& u, const Vector3<T>& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

template <typename T>
inline Vector3<T> cross(const Vector3<T>& u, const Vector3<T>& v)
{
    return Vector3<T>{
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    };
}

template <typename T>
inline T lengthSquared(const Vector3<T>& v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

template <typename T, typename Float = std::conditional_t<std::is_floating_point_v<T>, T, float>>
inline Float length(const Vector3<T>& v)
{
    const T x = lengthSquared(v);

    return std::sqrt(static_cast<Float>(x));
}

template <typename T>
inline T distanceSquared(const Vector3<T>& u, const Vector3<T>& v)
{
    return lengthSquared(u - v);
}

template <typename T, typename Float = std::conditional_t<std::is_floating_point_v<T>, T, float>>
inline Float distance(const Vector3<T>& u, const Vector3<T>& v)
{
    const T x = distanceSquared(u, v);

    return std::sqrt(static_cast<Float>(x));
}

template <typename T>
requires std::floating_point<T>
inline Vector3<T> normalize(const Vector3<T>& v)
{
    return v / length(v);
}

using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;
using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;

#endif
