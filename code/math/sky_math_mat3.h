#pragma once

#include "sky_math_types.h"
#include "sky_math_vec3.h"
#include "sky_math.h"

inline Mat3
operator+(const Mat3 &A, const Mat3 &B)
{
    return Mat3{
        A.m00 + B.m00, A.m01 + B.m01, A.m02 + B.m02,
        A.m10 + B.m10, A.m11 + B.m11, A.m12 + B.m12,
        A.m20 + B.m20, A.m21 + B.m21, A.m22 + B.m22};
}

inline Mat3 &
operator+=(Mat3 &A, const Mat3 &B)
{
    A = A + B;
    return A;
}


inline Mat3
operator-(const Mat3 &M)
{
    return Mat3{
        -M.m00, -M.m01, -M.m02,
        -M.m10, -M.m11, -M.m12,
        -M.m20, -M.m21, -M.m22};
}

inline Mat3
operator-(const Mat3 &A, const Mat3 &B)
{
    return Mat3{
        A.m00 - B.m00, A.m01 - B.m01, A.m02 - B.m02,
        A.m10 - B.m10, A.m11 - B.m11, A.m12 - B.m12,
        A.m20 - B.m20, A.m21 - B.m21, A.m22 - B.m22};
}

inline Mat3 &
operator-=(Mat3 &A, const Mat3 &B)
{
    A = A - B;
    return A;
}


inline Mat3
operator*(const Mat3 &M, float f)
{
    return Mat3{
        M.m00 * f, M.m01 * f, M.m02 * f,
        M.m10 * f, M.m11 * f, M.m12 * f,
        M.m20 * f, M.m21 * f, M.m22 * f};
}

inline Mat3
operator*(float f, const Mat3 &M)
{
    return M * f;
}

inline Mat3 &
operator*=(Mat3 &M, float f)
{
    M = M * f;
    return M;
}

inline Vec3
operator*(const Vec3 &v, const Mat3 &M)
{
    return Vec3{
        v.x * M.m00 + v.y * M.m10 + v.z * M.m20,
        v.x * M.m01 + v.y * M.m11 + v.z * M.m21,
        v.x * M.m02 + v.y * M.m12 + v.z * M.m22};
}

inline Mat3
operator*(const Mat3 &A, const Mat3 &B)
{
    Mat3 C;

    C.m00 = A.m00 * B.m00 + A.m01 * B.m10 + A.m02 * B.m20;
    C.m01 = A.m00 * B.m01 + A.m01 * B.m11 + A.m02 * B.m21;
    C.m02 = A.m00 * B.m02 + A.m01 * B.m12 + A.m02 * B.m22;

    C.m10 = A.m10 * B.m00 + A.m11 * B.m10 + A.m12 * B.m20;
    C.m11 = A.m10 * B.m01 + A.m11 * B.m11 + A.m12 * B.m21;
    C.m12 = A.m10 * B.m02 + A.m11 * B.m12 + A.m12 * B.m22;

    C.m20 = A.m20 * B.m00 + A.m21 * B.m10 + A.m22 * B.m20;
    C.m21 = A.m20 * B.m01 + A.m21 * B.m11 + A.m22 * B.m21;
    C.m22 = A.m20 * B.m02 + A.m21 * B.m12 + A.m22 * B.m22;

    return C;
}


inline Mat3
operator/(const Mat3 &M, float f)
{
    return Mat3{
        M.m00 / f, M.m01 / f, M.m02 / f,
        M.m10 / f, M.m11 / f, M.m12 / f,
        M.m20 / f, M.m21 / f, M.m22 / f};
}

inline Mat3
operator/(float f, const Mat3 &M)
{
    return M / f;
}

inline Mat3 &
operator/=(Mat3 &M, float f)
{
    M = M / f;
    return M;
}


inline const float &
mat3_at(const Mat3 &M, int i)
{
    return *((float *)(&M) + i);
}

inline float &
mat3_at(Mat3 &M, int i)
{
    return *((float *)(&M) + i);
}


inline Mat3
mat3_identity()
{
    return Mat3{
        1, 0, 0,
        0, 1, 0,
        0, 0, 1};
}

inline Mat3
mat3_transpose(const Mat3 &M)
{
    return Mat3{
        M.m00, M.m10, M.m20,
        M.m01, M.m11, M.m21,
        M.m02, M.m12, M.m22};
}

inline float
mat3_det(const Mat3 &M)
{
    return
        + M.m00 * (M.m11 * M.m22 - M.m12 * M.m21)
        - M.m01 * (M.m10 * M.m22 - M.m12 * M.m20)
        + M.m02 * (M.m10 * M.m21 - M.m11 * M.m20);
}

inline bool
mat3_invertible(const Mat3 &M)
{
    return mat3_det(M) != 0.0f;
}

inline Mat3
mat3_inverse(const Mat3 &M)
{
    float d = mat3_det(M);
    if (d == 0)
        return Mat3{};

    /*
        * 1- matrix of minors
        * 2- matrix of cofactors
        * 3- adjoint (transpose)
        * 4- multiply by 1 / det
        *
        * link: https://www.mathsisfun.com/algebra/matrix-inverse-minors-cofactors-adjugate.html
        */

    return (1.0f / d) * Mat3{
        // m00
        + (M.m11 * M.m22 - M.m12 * M.m21),
        // m10
        - (M.m01 * M.m22 - M.m02 * M.m21),
        // m20
        + (M.m01 * M.m12 - M.m02 * M.m11),

        // m01
        - (M.m10 * M.m22 - M.m12 * M.m20),
        // m11
        + (M.m00 * M.m22 - M.m02 * M.m20),
        // m21
        - (M.m00 * M.m12 - M.m02 * M.m10),

        // m02
        + (M.m10 * M.m21 - M.m11 * M.m20),
        // m12
        - (M.m00 * M.m21 - M.m01 * M.m20),
        // m22
        + (M.m00 * M.m11 - M.m01 * M.m10)};
}

inline Vec3
mat3_axis_x(const Mat3 &M)
{
    return vec3_normalize(Vec3{M.m00, M.m01, M.m02});
}

inline Vec3
mat3_axis_y(const Mat3 &M)
{
    return vec3_normalize(Vec3{M.m10, M.m11, M.m12});
}

inline Vec3
mat3_axis_z(const Mat3 &M)
{
    return vec3_normalize(Vec3{M.m20, M.m21, M.m22});
}

inline Mat3
mat3_translation_2d(float dx, float dy)
{
    return Mat3{
         1,  0,  0,
         0,  1,  0,
        dx, dy,  1};
}

inline Mat3
mat3_rotation_2d(float theta)
{
    float c = sky_cos(theta);
    float s = sky_sin(theta);

    return Mat3{
         c,  s,  0,
        -s,  c,  0,
         0,  0,  1};
}

inline Mat3
mat3_scaling_2d(float sx, float sy)
{
    return Mat3{
        sx,  0,  0,
         0, sy,  0,
         0,  0,  1};
}

inline Mat3
mat3_rotation_x(float pitch)
{
    float c = sky_cos(pitch);
    float s = sky_sin(pitch);

    return Mat3{
        1,  0,  0,
        0,  c,  s,
        0, -s,  c};
}

inline Mat3
mat3_rotation_y(float yaw)
{
    float c = sky_cos(yaw);
    float s = sky_sin(yaw);

    return Mat3{
        c,  0, -s,
        0,  1,  0,
        s,  0,  c};
}

inline Mat3
mat3_rotation_z(float roll)
{
    float c = sky_cos(roll);
    float s = sky_sin(roll);

    return Mat3{
         c,  s,  0,
        -s,  c,  0,
         0,  0,  1};
}

inline Mat3
mat3_scaling(float sx, float sy, float sz)
{
    return Mat3{
        sx,  0,  0,
         0, sy,  0,
         0,  0, sz};
}