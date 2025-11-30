#ifndef MATH_MATH_HPP
#define MATH_MATH_HPP

inline constexpr float PiOver180 = 0x1.1df46ap-6f;

inline float degToRad(float angle)
{
    return angle * PiOver180;
}

#endif
