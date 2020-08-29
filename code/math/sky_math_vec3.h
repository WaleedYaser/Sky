#pragma once

#include "sky_math_types.h"
#include "sky_math.h"

inline Vec3
operator+(const Vec3 &a, const Vec3 &b)
{
    return Vec3{a.x + b.x, a.y + b.y, a.z + b.z};
}

inline Vec3 &
operator+=(Vec3 &a, const Vec3 &b)
{
    a = a + b;
    return a;
}


inline Vec3
operator-(const Vec3 &v)
{
    return Vec3{-v.x, -v.y, -v.z};
}

inline Vec3
operator-(const Vec3 &a, const Vec3 &b)
{
    return Vec3{a.x - b.x, a.y - b.y, a.z - b.z};
}

inline Vec3 &
operator-=(Vec3 &a, const Vec3 &b)
{
    a = a - b;
    return a;
}


inline Vec3
operator*(const Vec3 &v, float f)
{
    return Vec3{v.x * f, v.y * f, v.z * f};
}

inline Vec3
operator*(float f, const Vec3 &v)
{
    return v * f;
}

inline Vec3 &
operator*=(Vec3 &v, float f)
{
    v = v * f;
    return v;
}


inline Vec3
operator/(const Vec3 &v, float f)
{
    return v * (1.0f / f);
}

inline Vec3 &
operator/=(Vec3 &v, float f)
{
    v = v / f;
    return v;
}


inline float
vec3_norm(const Vec3 &v)
{
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}

inline float
vec3_length(const Vec3 &v)
{
    return sky_sqrt(vec3_norm(v));
}

inline Vec3
vec3_normalize(const Vec3 &v)
{
    return v / vec3_length(v);
}


inline float
vec3_dot(const Vec3 &a, const Vec3 &b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline Vec3
vec3_cross(const Vec3 &a, const Vec3 &b)
{
    return Vec3{
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x};
}