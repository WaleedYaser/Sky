#pragma once

#include "sky_math_types.h"
#include "sky_math.h"

inline Vec4
operator+(const Vec4 &a, const Vec4 &b)
{
    return Vec4{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

inline Vec4 &
operator+=(Vec4 &a, const Vec4 &b)
{
    a = a + b;
    return a;
}


inline Vec4
operator-(const Vec4 &v)
{
    return Vec4{-v.x, -v.y, -v.z, -v.w};
}

inline Vec4
operator-(const Vec4 &a, const Vec4 &b)
{
    return Vec4{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

inline Vec4 &
operator-=(Vec4 &a, const Vec4 &b)
{
    a = a - b;
    return a;
}


inline Vec4
operator*(const Vec4 &v, float f)
{
    return Vec4{v.x * f, v.y * f, v.z * f, v.w * f};
}

inline Vec4
operator*(float f, const Vec4 &v)
{
    return v * f;
}

inline Vec4 &
operator*=(Vec4 &v, float f)
{
    v = v * f;
    return v;
}


inline Vec4
operator/(const Vec4 &v, float f)
{
    return v * (1.0f / f);
}

inline Vec4 &
operator/=(Vec4 &v, float f)
{
    v = v / f;
    return v;
}


inline float
vec4_norm(const Vec4 &v)
{
    return (v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

inline float
vec4_length(const Vec4 &v)
{
    return sky_sqrt(vec4_norm(v));
}

inline Vec4
vec4_normalize(const Vec4 &v)
{
    return v / vec4_length(v);
}


inline float
vec4_dot(const Vec4 &a, const Vec4 &b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}