#pragma once

#include "sky_math_types.h"
#include "sky_math_vec2.h"
#include "sky_math.h"

inline Mat2
operator+(const Mat2 &A, const Mat2 &B)
{
    return Mat2{
        A.m00 + B.m00, A.m01 + B.m01,
        A.m10 + B.m10, A.m11 + B.m11};
}

inline Mat2 &
operator+=(Mat2 &A, const Mat2 &B)
{
    A = A + B;
    return A;
}


inline Mat2
operator-(const Mat2 &M)
{
    return Mat2{
        -M.m00, -M.m01,
        -M.m10, -M.m11};
}

inline Mat2
operator-(const Mat2 &A, const Mat2 &B)
{
    return Mat2{
        A.m00 - B.m00, A.m01 - B.m01,
        A.m10 - B.m10, A.m11 - B.m11};
}

inline Mat2 &
operator-=(Mat2 &A, const Mat2 &B)
{
    A = A - B;
    return A;
}


inline Mat2
operator*(const Mat2 &M, float f)
{
    return Mat2{
        M.m00 * f, M.m01 * f,
        M.m10 * f, M.m11 * f};
}

inline Mat2
operator*(float f, const Mat2 &M)
{
    return M * f;
}

inline Mat2 &
operator*=(Mat2 &M, float f)
{
    M = M * f;
    return M;
}

inline Vec2
operator*(const Vec2 &v, const Mat2 &M)
{
    return Vec2{
        v.x * M.m00 + v.y * M.m10,
        v.x * M.m01 + v.y * M.m11};
}

inline Mat2
operator*(const Mat2 &A, const Mat2 &B)
{
    Mat2 C;

    C.m00 = A.m00 * B.m00 + A.m01 * B.m10;
    C.m01 = A.m00 * B.m01 + A.m01 * B.m11;

    C.m10 = A.m10 * B.m00 + A.m11 * B.m10;
    C.m11 = A.m10 * B.m01 + A.m11 * B.m11;

    return C;
}


inline Mat2
operator/(const Mat2 &M, float f)
{
    return Mat2{
        M.m00 / f, M.m01 / f,
        M.m10 / f, M.m11 / f};
}

inline Mat2
operator/(float f, const Mat2 &M)
{
    return M / f;
}

inline Mat2 &
operator/=(Mat2 &M, float f)
{
    M = M / f;
    return M;
}


inline const float &
mat2_at(const Mat2 &M, int i)
{
    return *((float *)(&M) + i);
}

inline float &
mat2_at(Mat2 &M, int i)
{
    return *((float *)(&M) + i);
}


inline Mat2
mat2_identity()
{
    return Mat2{
        1, 0,
        0, 1};
}

inline Mat2
mat2_transpose(const Mat2 &M)
{
    return Mat2{
        M.m00, M.m10,
        M.m01, M.m11};
}

inline float
mat2_det(const Mat2 &M)
{
    return M.m00 * M.m11 - M.m01 * M.m10;
}

inline bool
mat2_invertible(const Mat2 &M)
{
    return mat2_det(M) != 0.0f;
}

inline Mat2
mat2_inverse(const Mat2 &M)
{
    float d = mat2_det(M);
    if (d == 0)
        return Mat2{};

    return (1.0f / d) * Mat2{
         M.m11, -M.m01,
        -M.m10,  M.m00};
}

inline Vec2
mat2_axis_x(const Mat2 &M)
{
    return vec2_normalize(Vec2{M.m00, M.m01});
}

inline Vec2
mat2_axis_y(const Mat2 &M)
{
    return vec2_normalize(Vec2{M.m10, M.m11});
}

inline Mat2
mat2_rotation(float theta)
{
    float c = sky_cos(theta);
    float s = sky_sin(theta);

    return Mat2{
         c,  s,
        -s,  c};
}

inline Mat2
mat2_scaling(float sx, float sy)
{
    return Mat2{
        sx,  0,
         0, sy};
}