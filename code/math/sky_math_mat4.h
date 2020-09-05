#pragma once

#include "sky_math_types.h"
#include "sky_math_vec3.h"
#include "sky_math_vec4.h"
#include "sky_math.h"

inline Mat4
operator+(const Mat4 &A, const Mat4 &B)
{
    return Mat4{
        A.m00 + B.m00, A.m01 + B.m01, A.m02 + B.m02, A.m03 + B.m03,
        A.m10 + B.m10, A.m11 + B.m11, A.m12 + B.m12, A.m13 + B.m13,
        A.m20 + B.m20, A.m21 + B.m21, A.m22 + B.m22, A.m23 + B.m23,
        A.m30 + B.m30, A.m31 + B.m31, A.m32 + B.m32, A.m33 + B.m33};
}

inline Mat4 &
operator+=(Mat4 &A, const Mat4 &B)
{
    A = A + B;
    return A;
}


inline Mat4
operator-(const Mat4 &M)
{
    return Mat4{
        -M.m00, -M.m01, -M.m02, -M.m03,
        -M.m10, -M.m11, -M.m12, -M.m13,
        -M.m20, -M.m21, -M.m22, -M.m23,
        -M.m30, -M.m31, -M.m32, -M.m33};
}

inline Mat4
operator-(const Mat4 &A, const Mat4 &B)
{
    return Mat4{
        A.m00 - B.m00, A.m01 - B.m01, A.m02 - B.m02, A.m03 - B.m03,
        A.m10 - B.m10, A.m11 - B.m11, A.m12 - B.m12, A.m13 - B.m13,
        A.m20 - B.m20, A.m21 - B.m21, A.m22 - B.m22, A.m23 - B.m23,
        A.m30 - B.m30, A.m31 - B.m31, A.m32 - B.m32, A.m33 - B.m33};
}

inline Mat4 &
operator-=(Mat4 &A, const Mat4 &B)
{
    A = A - B;
    return A;
}


inline Mat4
operator*(const Mat4 &M, float f)
{
    return Mat4{
        M.m00 * f, M.m01 * f, M.m02 * f, M.m03 * f,
        M.m10 * f, M.m11 * f, M.m12 * f, M.m13 * f,
        M.m20 * f, M.m21 * f, M.m22 * f, M.m23 * f,
        M.m30 * f, M.m31 * f, M.m32 * f, M.m33 * f};
}

inline Mat4
operator*(float f, const Mat4 &M)
{
    return M * f;
}

inline Mat4 &
operator*=(Mat4 &M, float f)
{
    M = M * f;
    return M;
}

inline Vec4
operator*(const Vec4 &v, const Mat4 &M)
{
    return Vec4{
        v.x * M.m00 + v.y * M.m10 + v.z * M.m20 + v.w * M.m30,
        v.x * M.m01 + v.y * M.m11 + v.z * M.m21 + v.w * M.m31,
        v.x * M.m02 + v.y * M.m12 + v.z * M.m22 + v.w * M.m32,
        v.x * M.m03 + v.y * M.m13 + v.z * M.m23 + v.w * M.m33};
}

inline Mat4
operator*(const Mat4 &A, const Mat4 &B)
{
    Mat4 C;

    C.m00 = A.m00 * B.m00 + A.m01 * B.m10 + A.m02 * B.m20 + A.m03 * B.m30;
    C.m01 = A.m00 * B.m01 + A.m01 * B.m11 + A.m02 * B.m21 + A.m03 * B.m31;
    C.m02 = A.m00 * B.m02 + A.m01 * B.m12 + A.m02 * B.m22 + A.m03 * B.m32;
    C.m03 = A.m00 * B.m03 + A.m01 * B.m13 + A.m02 * B.m23 + A.m03 * B.m33;

    C.m10 = A.m10 * B.m00 + A.m11 * B.m10 + A.m12 * B.m20 + A.m13 * B.m30;
    C.m11 = A.m10 * B.m01 + A.m11 * B.m11 + A.m12 * B.m21 + A.m13 * B.m31;
    C.m12 = A.m10 * B.m02 + A.m11 * B.m12 + A.m12 * B.m22 + A.m13 * B.m32;
    C.m13 = A.m10 * B.m03 + A.m11 * B.m13 + A.m12 * B.m23 + A.m13 * B.m33;

    C.m20 = A.m20 * B.m00 + A.m21 * B.m10 + A.m22 * B.m20 + A.m23 * B.m30;
    C.m21 = A.m20 * B.m01 + A.m21 * B.m11 + A.m22 * B.m21 + A.m23 * B.m31;
    C.m22 = A.m20 * B.m02 + A.m21 * B.m12 + A.m22 * B.m22 + A.m23 * B.m32;
    C.m23 = A.m20 * B.m03 + A.m21 * B.m13 + A.m22 * B.m23 + A.m23 * B.m33;

    C.m30 = A.m30 * B.m00 + A.m31 * B.m10 + A.m32 * B.m20 + A.m33 * B.m30;
    C.m31 = A.m30 * B.m01 + A.m31 * B.m11 + A.m32 * B.m21 + A.m33 * B.m31;
    C.m32 = A.m30 * B.m02 + A.m31 * B.m12 + A.m32 * B.m22 + A.m33 * B.m32;
    C.m33 = A.m30 * B.m03 + A.m31 * B.m13 + A.m32 * B.m23 + A.m33 * B.m33;

    return C;
}


inline Mat4
operator/(const Mat4 &M, float f)
{
    return Mat4{
        M.m00 / f, M.m01 / f, M.m02 / f, M.m03 / f,
        M.m10 / f, M.m11 / f, M.m12 / f, M.m13 / f,
        M.m20 / f, M.m21 / f, M.m22 / f, M.m23 / f,
        M.m30 / f, M.m31 / f, M.m32 / f, M.m33 / f};
}

inline Mat4
operator/(float f, const Mat4 &M)
{
    return M / f;
}

inline Mat4 &
operator/=(Mat4 &M, float f)
{
    M = M / f;
    return M;
}


inline const float &
mat4_at(const Mat4 &M, int i)
{
    return *((float *)(&M) + i);
}

inline float &
mat4_at(Mat4 &M, int i)
{
    return *((float *)(&M) + i);
}


inline Mat4
mat4_identity()
{
    return Mat4{
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1};
}

inline Mat4
mat4_transpose(const Mat4 &M)
{
    return Mat4{
        M.m00, M.m10, M.m20, M.m30,
        M.m01, M.m11, M.m21, M.m31,
        M.m02, M.m12, M.m22, M.m32,
        M.m03, M.m13, M.m23, M.m33};
}

inline float
mat4_det(const Mat4 &M)
{
    /*
        * before optimization:
        + M.m00 * (
            + M.m11 * (M.m22 * M.m33 - M.m23 * M.m32)
            - M.m12 * (M.m21 * M.m33 - M.m23 * M.m31)
            + M.m13 * (M.m21 * M.m32 - M.m22 * M.m31))
        - M.m01 * (
            + M.m10 * (M.m22 * M.m33 - M.m23 * M.m32)
            - M.m12 * (M.m20 * M.m33 - M.m23 * M.m30)
            + M.m13 * (M.m20 * M.m32 - M.m22 * M.m30))
        + M.m02 * (
            + M.m10 * (M.m21 * M.m33 - M.m23 * M.m31)
            - M.m11 * (M.m20 * M.m33 - M.m23 * M.m30)
            + M.m13 * (M.m20 * M.m31 - M.m21 * M.m30))
        - M.m03 * (
            + M.m10 * (M.m21 * M.m32 - M.m22 * M.m31)
            - M.m11 * (M.m20 * M.m32 - M.m22 * M.m30)
            + M.m12 * (M.m20 * M.m31 - M.m21 * M.m30));
        */
    return
        (M.m00 * M.m11 - M.m01 * M.m10) * (M.m22 * M.m33 - M.m23 * M.m32) -
        (M.m00 * M.m12 - M.m02 * M.m10) * (M.m21 * M.m33 - M.m23 * M.m31) +
        (M.m00 * M.m13 - M.m03 * M.m10) * (M.m21 * M.m32 - M.m22 * M.m31) +
        (M.m01 * M.m12 - M.m02 * M.m11) * (M.m20 * M.m33 - M.m23 * M.m30) -
        (M.m01 * M.m13 - M.m03 * M.m11) * (M.m20 * M.m32 - M.m22 * M.m30) +
        (M.m02 * M.m13 - M.m03 * M.m12) * (M.m20 * M.m31 - M.m21 * M.m30);
}

inline bool
mat4_invertible(const Mat4 &M)
{
    return mat4_det(M) != 0.0f;
}

inline Mat4
mat4_inverse(const Mat4 &M)
{
    float d = mat4_det(M);
    if (d == 0)
        return Mat4{};

    /*
        * 1- matrix of minors
        * 2- matrix of cofactors
        * 3- adjoint (transpose)
        * 4- multiply by 1 / det
        *
        * link: https://www.mathsisfun.com/algebra/matrix-inverse-minors-cofactors-adjugate.html
        */

    return (1.0f / d) * Mat4{
        // m00
        + M.m11 * (M.m22 * M.m33 - M.m23 * M.m32)
        - M.m12 * (M.m21 * M.m33 - M.m23 * M.m31)
        + M.m13 * (M.m21 * M.m32 - M.m22 * M.m31),
        // m10
        - M.m01 * (M.m22 * M.m33 - M.m23 * M.m32)
        + M.m02 * (M.m21 * M.m33 - M.m23 * M.m31)
        - M.m03 * (M.m21 * M.m32 - M.m22 * M.m31),
        // m20
        + M.m01 * (M.m12 * M.m33 - M.m13 * M.m32)
        - M.m02 * (M.m11 * M.m33 - M.m13 * M.m31)
        + M.m03 * (M.m11 * M.m32 - M.m12 * M.m31),
        // m30
        - M.m01 * (M.m12 * M.m23 - M.m13 * M.m22)
        + M.m02 * (M.m11 * M.m23 - M.m13 * M.m21)
        - M.m03 * (M.m11 * M.m22 - M.m12 * M.m21),


        // m01
        - M.m10 * (M.m22 * M.m33 - M.m23 * M.m32)
        + M.m12 * (M.m20 * M.m33 - M.m23 * M.m30)
        - M.m13 * (M.m20 * M.m32 - M.m22 * M.m30),
        // m11
        + M.m00 * (M.m22 * M.m33 - M.m23 * M.m32)
        - M.m02 * (M.m20 * M.m33 - M.m23 * M.m30)
        + M.m03 * (M.m20 * M.m32 - M.m22 * M.m30),
        // m21
        - M.m00 * (M.m12 * M.m33 - M.m13 * M.m32)
        + M.m02 * (M.m10 * M.m33 - M.m13 * M.m30)
        - M.m03 * (M.m10 * M.m32 - M.m12 * M.m30),
        // m31
        + M.m00 * (M.m12 * M.m23 - M.m13 * M.m22)
        - M.m02 * (M.m10 * M.m23 - M.m13 * M.m20)
        + M.m03 * (M.m10 * M.m22 - M.m12 * M.m20),


        // m02
        + M.m10 * (M.m21 * M.m33 - M.m23 * M.m31)
        - M.m11 * (M.m20 * M.m33 - M.m23 * M.m30)
        + M.m13 * (M.m20 * M.m31 - M.m21 * M.m30),
        // m12
        - M.m00 * (M.m21 * M.m33 - M.m23 * M.m31)
        + M.m01 * (M.m20 * M.m33 - M.m23 * M.m30)
        - M.m03 * (M.m20 * M.m31 - M.m21 * M.m30),
        // m22
        + M.m00 * (M.m11 * M.m33 - M.m13 * M.m31)
        - M.m01 * (M.m10 * M.m33 - M.m13 * M.m30)
        + M.m03 * (M.m10 * M.m31 - M.m11 * M.m30),
        // m32
        - M.m00 * (M.m11 * M.m23 - M.m13 * M.m21)
        + M.m01 * (M.m10 * M.m23 - M.m13 * M.m20)
        - M.m03 * (M.m10 * M.m21 - M.m11 * M.m20),


        // m03
        - M.m10 * (M.m21 * M.m32 - M.m22 * M.m31)
        + M.m11 * (M.m20 * M.m32 - M.m22 * M.m30)
        - M.m12 * (M.m20 * M.m31 - M.m21 * M.m30),
        // m13
        + M.m00 * (M.m21 * M.m32 - M.m22 * M.m31)
        - M.m01 * (M.m20 * M.m32 - M.m22 * M.m30)
        + M.m02 * (M.m20 * M.m31 - M.m21 * M.m30),
        // m23
        - M.m00 * (M.m11 * M.m32 - M.m12 * M.m31)
        + M.m01 * (M.m10 * M.m32 - M.m12 * M.m30)
        - M.m02 * (M.m10 * M.m31 - M.m11 * M.m30),
        // m33
        + M.m00 * (M.m11 * M.m22 - M.m12 * M.m21)
        - M.m01 * (M.m10 * M.m22 - M.m12 * M.m20)
        + M.m02 * (M.m10 * M.m21 - M.m11 * M.m20)};
}

// TODO(Waleed): add unittest
inline Mat4
mat4_coord(Vec3 right, Vec3 up, Vec3 forward)
{
    right = vec3_normalize(right);
    up = vec3_normalize(up);
    forward = vec3_normalize(forward);

    return Mat4{
        right.x,   right.y,   right.z,   0.0f,
        up.x,      up.y,      up.z,      0.0f,
        forward.x, forward.y, forward.z, 0.0f,
        0.0f,      0.0f,      0.0f,      1.0f};
}

inline Vec3
mat4_axis_x(const Mat4 &M)
{
    return vec3_normalize(Vec3{M.m00, M.m01, M.m02});
}

inline Vec3
mat4_axis_y(const Mat4 &M)
{
    return vec3_normalize(Vec3{M.m10, M.m11, M.m12});
}

inline Vec3
mat4_axis_z(const Mat4 &M)
{
    return vec3_normalize(Vec3{M.m20, M.m21, M.m22});
}

inline Mat4
mat4_translation(float dx, float dy, float dz)
{
    return Mat4{
         1,  0,  0, 0,
         0,  1,  0, 0,
         0,  0,  1, 0,
        dx, dy, dz, 1};
}

inline Mat4
mat4_rotation_x(float pitch)
{
    float c = sky_cos(pitch);
    float s = sky_sin(pitch);

    return Mat4{
        1,  0,  0,  0,
        0,  c,  s,  0,
        0, -s,  c,  0,
        0,  0,  0,  1};
}

inline Mat4
mat4_rotation_y(float yaw)
{
    float c = sky_cos(yaw);
    float s = sky_sin(yaw);

    return Mat4{
        c,  0, -s,  0,
        0,  1,  0,  0,
        s,  0,  c,  0,
        0,  0,  0,  1};
}

inline Mat4
mat4_rotation_z(float roll)
{
    float c = sky_cos(roll);
    float s = sky_sin(roll);

    return Mat4{
         c,  s,  0,  0,
        -s,  c,  0,  0,
         0,  0,  1,  0,
         0,  0,  0,  1};
}

inline Mat4
mat4_scaling(float sx, float sy, float sz)
{
    return Mat4{
        sx,  0,  0, 0,
         0, sy,  0, 0,
         0,  0, sz, 0,
         0,  0,  0, 1};
}

// TODO(Waleed): add unittests
inline Mat4
mat4_ortho(float left, float right, float bottom, float top, float znear, float zfar)
{
    Mat4 M{};

    M.m00 = 2.0f / (right - left);
    M.m30 = -(right + left) / (right - left);

    M.m11 = 2.0f / (top - bottom);
    M.m31 = -(top + bottom) / (top - bottom);

    // to map z to [0, 1] use
    // M.m22 = -1.0f / (far - near)
    // M.m32 = -near / (far - near)
    M.m22 = -2.0f / (zfar - znear);
    M.m32 = -(zfar + znear) / (zfar - znear);

    M.m33 = 1.0f;

    return M;
}

// TODO(Waleed): add unittests
inline Mat4
mat4_prespective(float fovy, float aspect, float znear, float zfar)
{
    Mat4 M{};

    float h = sky_tan(fovy / 2.0f);
    float w = aspect * h;

    M.m00 = 1.0f / w;
    M.m11 = 1.0f / h;

    // to map z to [0, 1] use
    // M.m22 = -far / (far - near)
    // M.m32 = -far * near / (far - near)
    M.m22 = -(zfar + znear) / (zfar - znear);
    M.m23 = -1.0f;
    M.m32 = -(2.0f * zfar * znear) / (zfar - znear);

    return M;
}