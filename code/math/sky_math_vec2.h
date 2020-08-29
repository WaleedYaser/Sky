#pragma once

#include "sky_math_types.h"
#include "sky_math.h"

inline Vec2
operator+(const Vec2 &a, const Vec2 &b)
{
    return Vec2{a.x + b.x, a.y + b.y};
}

inline Vec2 &
operator+=(Vec2 &a, const Vec2 &b)
{
    a = a + b;
    return a;
}


inline Vec2
operator-(const Vec2 &v)
{
    return Vec2{-v.x, -v.y};
}

inline Vec2
operator-(const Vec2 &a, const Vec2 &b)
{
    return Vec2{a.x - b.x, a.y - b.y};
}

inline Vec2 &
operator-=(Vec2 &a, const Vec2 &b)
{
    a = a - b;
    return a;
}


inline Vec2
operator*(const Vec2 &v, float f)
{
    return Vec2{v.x * f, v.y * f};
}

inline Vec2
operator*(float f, const Vec2 &v)
{
    return v * f;
}

inline Vec2 &
operator*=(Vec2 &v, float f)
{
    v = v * f;
    return v;
}


inline Vec2
operator/(const Vec2 &v, float f)
{
    return v * (1.0f / f);
}

inline Vec2 &
operator/=(Vec2 &v, float f)
{
    v = v / f;
    return v;
}


inline float
vec2_norm(const Vec2 &v)
{
    return (v.x * v.x + v.y * v.y);
}

inline float
vec2_length(const Vec2 &v)
{
    return sky_sqrt(vec2_norm(v));
}

inline Vec2
vec2_normalize(const Vec2 &v)
{
    return v / vec2_length(v);
}


inline float
vec2_dot(const Vec2 &a, const Vec2 &b)
{
    return (a.x * b.x + a.y * b.y);
}

inline float
vec2_cross(const Vec2 &a, const Vec2 &b)
{
    return (a.x * b.y - a.y * b.x);
}