#pragma once

#define PI        (3.14159265359f)
#define PI_TIME_2 (PI * 2.0f)
#define PI_OVER_2 (PI / 2.0f)

#define RAD_TO_DEGREE (360.0f / PI_TIME_2)
#define DEGREE_TO_RAD (1.0f / RAD_TO_DEGREE)

typedef struct Vec2
{
    float x, y;
} Vec2;

typedef struct Vec3
{
    float x, y, z;
} Vec3;

typedef struct Vec4
{
    float x, y, z, w;
} Vec4;

typedef struct Mat2
{
    float m00, m01;
    float m10, m11;
} Mat2;

typedef struct Mat3
{
    float m00, m01, m02;
    float m10, m11, m12;
    float m20, m21, m22;
} Mat3;

typedef struct Mat4
{
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
} Mat4;