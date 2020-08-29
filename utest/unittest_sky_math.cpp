#include "doctest.h"

#include <math/sky_math_types.h>
#include <math/sky_math_vec2.h>
#include <math/sky_math_vec3.h>
#include <math/sky_math_vec4.h>
#include <math/sky_math_mat2.h>
#include <math/sky_math_mat3.h>
#include <math/sky_math_mat4.h>
#include <math/sky_math_intersection.h>
#include <math/sky_math.h>

TEST_CASE("[ankh-math: radian/degree")
{
    SUBCASE("Case 01")
    {
        float rad1 = 0.785398f;

        float degree = RAD_TO_DEGREE * rad1;

        CHECK(degree == doctest::Approx(45));

        float rad2 = DEGREE_TO_RAD * degree;

        CHECK(rad2 == doctest::Approx(rad1));
    }

    SUBCASE("Case 02")
    {
        float degree1 = 220.0f;

        float rad = DEGREE_TO_RAD * degree1;

        CHECK(rad == doctest::Approx(3.83972f));

        float degree2 = RAD_TO_DEGREE * rad;

        CHECK(degree1 == doctest::Approx(degree2));
    }
}

TEST_CASE("[ankh-math]: vector creation")
{
    SUBCASE("Case 01")
    {
        Vec2 a = Vec2{};
        Vec2 b = Vec2{1.0f, 2.0f};

        CHECK(a.x == 0);
        CHECK(a.y == 0);

        CHECK(b.x == 1.0f);
        CHECK(b.y == 2.0f);
    }

    SUBCASE("Case 02")
    {
        Vec3 a = Vec3{};
        Vec3 b = Vec3{1.0f, 2.0f, 3.0f};

        CHECK(a.x == 0);
        CHECK(a.y == 0);
        CHECK(a.z == 0);

        CHECK(b.x == 1.0f);
        CHECK(b.y == 2.0f);
        CHECK(b.z == 3.0f);
    }

    SUBCASE("Case 03")
    {
        Vec4 a = Vec4{};
        Vec4 b = Vec4{1.0f, 2.0f, 3.0f, 4.0f};

        CHECK(a.x == 0);
        CHECK(a.y == 0);
        CHECK(a.z == 0);
        CHECK(a.w == 0);

        CHECK(b.x == 1.0f);
        CHECK(b.y == 2.0f);
        CHECK(b.z == 3.0f);
        CHECK(b.w == 4.0f);
    }
}

TEST_CASE("[ankh-math]: vector addition")
{
    SUBCASE("Case 01")
    {
        Vec2 a = Vec2{3.0f, 7.0f};
        Vec2 b = Vec2{1.0f, -4.0f};

        Vec2 c = a + b;

        CHECK(c.x == a.x + b.x);
        CHECK(c.y == a.y + b.y);
    }

    SUBCASE("Case 02")
    {
        Vec2 a = Vec2{9.0f, 2.0f};
        Vec2 b = Vec2{10.0f, 31.0f};

        Vec2 c = a;
        c += b;

        CHECK(c.x == a.x + b.x);
        CHECK(c.y == a.y + b.y);
    }

    SUBCASE("Case 03")
    {
        Vec3 a = Vec3{3.0f, 7.0f, 9.0f};
        Vec3 b = Vec3{1.0f, -4.0f, 8.5f};

        Vec3 c = a + b;

        CHECK(c.x == a.x + b.x);
        CHECK(c.y == a.y + b.y);
        CHECK(c.z == a.z + b.z);
    }

    SUBCASE("Case 04")
    {
        Vec3 a = Vec3{9.0f, 2.0f, 1.0f};
        Vec3 b = Vec3{10.0f, 31.0f, -87.0f};

        Vec3 c = a;
        c += b;

        CHECK(c.x == a.x + b.x);
        CHECK(c.y == a.y + b.y);
        CHECK(c.z == a.z + b.z);
    }

    SUBCASE("Case 05")
    {
        Vec4 a = Vec4{3.0f, 7.0f, 9.0f, 7.0f};
        Vec4 b = Vec4{1.0f, -4.0f, 8.5f, 5.0f};

        Vec4 c = a + b;

        CHECK(c.x == a.x + b.x);
        CHECK(c.y == a.y + b.y);
        CHECK(c.z == a.z + b.z);
        CHECK(c.w == a.w + b.w);
    }

    SUBCASE("Case 06")
    {
        Vec4 a = Vec4{9.0f, 2.0f, 1.0f, 30.0f};
        Vec4 b = Vec4{10.0f, 31.0f, -87.0f, 3.0f};

        Vec4 c = a;
        c += b;

        CHECK(c.x == a.x + b.x);
        CHECK(c.y == a.y + b.y);
        CHECK(c.z == a.z + b.z);
        CHECK(c.w == a.w + b.w);
    }
}

TEST_CASE("[ankh-math]: vector unary")
{
    SUBCASE("Case 01")
    {
        Vec2 v = Vec2{8.0f, 1.0f};

        Vec2 c = -v;

        CHECK(c.x == -v.x);
        CHECK(c.y == -v.y);
    }

    SUBCASE("Case 02")
    {
        Vec3 v = Vec3{8.0f, 1.0f, 11.0f};

        Vec3 c = -v;

        CHECK(c.x == -v.x);
        CHECK(c.y == -v.y);
        CHECK(c.z == -v.z);
    }

    SUBCASE("Case 02")
    {
        Vec4 v = Vec4{8.0f, 1.0f, 11.0f, 1.0f};

        Vec4 c = -v;

        CHECK(c.x == -v.x);
        CHECK(c.y == -v.y);
        CHECK(c.z == -v.z);
        CHECK(c.w == -v.w);
    }
}

TEST_CASE("[ankh-math]: vector subtraction")
{
    SUBCASE("Case 01")
    {
        Vec2 a = Vec2{-8.0f, 12.0f};
        Vec2 b = Vec2{90.0f, 1.0f};

        Vec2 c = a - b;

        CHECK(c.x == a.x - b.x);
        CHECK(c.y == a.y - b.y);
    }

    SUBCASE("Case 02")
    {
        Vec2 a = Vec2{1.0f, 2.0f};
        Vec2 b = Vec2{4.0f, 5.0f};

        Vec2 c = a;
        c -= b;

        CHECK(c.x == a.x - b.x);
        CHECK(c.y == a.y - b.y);
    }

    SUBCASE("Case 03")
    {
        Vec3 a = Vec3{-8.0f, 12.0f, 65.0f};
        Vec3 b = Vec3{90.0f, 1.0f, 8.0f};

        Vec3 c = a - b;

        CHECK(c.x == a.x - b.x);
        CHECK(c.y == a.y - b.y);
        CHECK(c.z == a.z - b.z);
    }

    SUBCASE("Case 04")
    {
        Vec3 a = Vec3{1.0f, 2.0f, 3.0f};
        Vec3 b = Vec3{4.0f, 5.0f, 6.0f};

        Vec3 c = a;
        c -= b;

        CHECK(c.x == a.x - b.x);
        CHECK(c.y == a.y - b.y);
        CHECK(c.z == a.z - b.z);
    }

    SUBCASE("Case 05")
    {
        Vec4 a = Vec4{-8.0f, 12.0f, 65.0f, 1.0f};
        Vec4 b = Vec4{90.0f, 1.0f, 8.0f, 33.0f};

        Vec4 c = a - b;

        CHECK(c.x == a.x - b.x);
        CHECK(c.y == a.y - b.y);
        CHECK(c.z == a.z - b.z);
        CHECK(c.w == a.w - b.w);
    }

    SUBCASE("Case 06")
    {
        Vec4 a = Vec4{1.0f, 2.0f, 3.0f, 11.0f};
        Vec4 b = Vec4{4.0f, 5.0f, 6.0f, -22.0f};

        Vec4 c = a;
        c -= b;

        CHECK(c.x == a.x - b.x);
        CHECK(c.y == a.y - b.y);
        CHECK(c.z == a.z - b.z);
        CHECK(c.w == a.w - b.w);
    }
}

TEST_CASE("[ankh-math]: vector multiplication")
{
    SUBCASE("Case 01")
    {
        Vec2 v  = Vec2{9.0f, 4.0f};
        float f = 5.0f;

        Vec2 c = v * f;

        CHECK(c.x == v.x * f);
        CHECK(c.y == v.y * f);
    }

    SUBCASE("Case 02")
    {
        Vec2 v  = Vec2{9.0f, 4.0f};
        float f = 5.0f;

        Vec2 c = f * v;

        CHECK(c.x == v.x * f);
        CHECK(c.y == v.y * f);
    }

    SUBCASE("Case 03")
    {
        Vec2 v  = Vec2{9.0f, 4.0f};
        float f = 5.0f;

        Vec2 c = v;
        c *= f;

        CHECK(c.x == v.x * f);
        CHECK(c.y == v.y * f);
    }

    SUBCASE("Case 04")
    {
        Vec3 v  = Vec3{9.0f, 4.0f, 1.0f};
        float f = 5.0f;

        Vec3 c = v * f;

        CHECK(c.x == v.x * f);
        CHECK(c.y == v.y * f);
        CHECK(c.z == v.z * f);
    }

    SUBCASE("Case 05")
    {
        Vec3 v  = Vec3{9.0f, 4.0f, 1.0f};
        float f = 5.0f;

        Vec3 c = f * v;

        CHECK(c.x == v.x * f);
        CHECK(c.y == v.y * f);
        CHECK(c.z == v.z * f);
    }

    SUBCASE("Case 06")
    {
        Vec3 v  = Vec3{9.0f, 4.0f, 1.0f};
        float f = 5.0f;

        Vec3 c = v;
        c *= f;

        CHECK(c.x == v.x * f);
        CHECK(c.y == v.y * f);
        CHECK(c.z == v.z * f);
    }

    SUBCASE("Case 07")
    {
        Vec4 v  = Vec4{9.0f, 4.0f, 1.0f, 5.0f};
        float f = 5.0f;

        Vec4 c = v * f;

        CHECK(c.x == v.x * f);
        CHECK(c.y == v.y * f);
        CHECK(c.z == v.z * f);
        CHECK(c.w == v.w * f);
    }

    SUBCASE("Case 08")
    {
        Vec4 v  = Vec4{9.0f, 4.0f, 1.0f, 5.0f};
        float f = 5.0f;

        Vec4 c = f * v;

        CHECK(c.x == v.x * f);
        CHECK(c.y == v.y * f);
        CHECK(c.z == v.z * f);
        CHECK(c.w == v.w * f);
    }

    SUBCASE("Case 09")
    {
        Vec4 v  = Vec4{9.0f, 4.0f, 1.0f, 5.0f};
        float f = 5.0f;

        Vec4 c = v;
        c *= f;

        CHECK(c.x == v.x * f);
        CHECK(c.y == v.y * f);
        CHECK(c.z == v.z * f);
        CHECK(c.w == v.w * f);
    }
}

TEST_CASE("[ankh-math]: vector division")
{
    SUBCASE("Case 01")
    {
        Vec2 v  = Vec2{20.0f, 30.0f};
        float f = 10.0f;

        Vec2 c = v / f;

        CHECK(c.x == v.x / f);
        CHECK(c.y == v.y / f);
    }

    SUBCASE("Case 02")
    {
        Vec2 v  = Vec2{20.0f, 30.0f};
        float f = 10.0f;

        Vec2 c = v;
        c /= f;

        CHECK(c.x == v.x / f);
        CHECK(c.y == v.y / f);
    }

    SUBCASE("Case 03")
    {
        Vec3 v  = Vec3{20.0f, 30.0f, 40.0f};
        float f = 10.0f;

        Vec3 c = v / f;

        CHECK(c.x == v.x / f);
        CHECK(c.y == v.y / f);
        CHECK(c.z == v.z / f);
    }

    SUBCASE("Case 04")
    {
        Vec3 v  = Vec3{20.0f, 30.0f, 40.0f};
        float f = 10.0f;

        Vec3 c = v;
        c /= f;

        CHECK(c.x == v.x / f);
        CHECK(c.y == v.y / f);
        CHECK(c.z == v.z / f);
    }

    SUBCASE("Case 05")
    {
        Vec4 v  = Vec4{20.0f, 30.0f, 40.0f, 50.f};
        float f = 10.0f;

        Vec4 c = v / f;

        CHECK(c.x == v.x / f);
        CHECK(c.y == v.y / f);
        CHECK(c.z == v.z / f);
    }

    SUBCASE("Case 06")
    {
        Vec4 v  = Vec4{20.0f, 30.0f, 40.0f, 50.f};
        float f = 10.0f;

        Vec4 c = v;
        c /= f;

        CHECK(c.x == v.x / f);
        CHECK(c.y == v.y / f);
        CHECK(c.z == v.z / f);
    }
}

TEST_CASE("[ankh-math]: vector norm")
{
    SUBCASE("Case 01")
    {
        Vec2 v  = Vec2{2.0f, 4.0f};
        float n = vec2_norm(v);

        CHECK(n == 20);
    }

    SUBCASE("Case 02")
    {
        Vec3 v  = Vec3{2.0f, 4.0f, 6.0f};
        float n = vec3_norm(v);

        CHECK(n == 56);
    }

    SUBCASE("Case 03")
    {
        Vec4 v  = Vec4{2.0f, 4.0f, 6.0f, 8.0f};
        float n = vec4_norm(v);

        CHECK(n == 120);
    }
}

TEST_CASE("[ankh-math]: vector length")
{
    SUBCASE("Case 01")
    {
        Vec2 v  = Vec2{2.0f, 4.0f};
        float l = vec2_length(v);

        CHECK(l == doctest::Approx(4.47).epsilon(0.01));
    }

    SUBCASE("Case 02")
    {
        Vec3 v  = Vec3{2.0f, 4.0f, 6.0f};
        float l = vec3_length(v);

        CHECK(l == doctest::Approx(7.48).epsilon(0.01));
    }

    SUBCASE("Case 03")
    {
        Vec4 v  = Vec4{2.0f, 4.0f, 6.0f, 8.0f};
        float l = vec4_length(v);

        CHECK(l == doctest::Approx(10.95).epsilon(0.01));
    }
}

TEST_CASE("[ankh-math]: vector normalize")
{
    SUBCASE("Case 01")
    {
        Vec2 v  = Vec2{2.0f, 4.0f};
        Vec2 n  = vec2_normalize(v);
        float l = vec2_length(n);

        CHECK(l == doctest::Approx(1.0f));
    }

    SUBCASE("Case 02")
    {
        Vec3 v  = Vec3{2.0f, 4.0f, 6.0f};
        Vec3 n  = vec3_normalize(v);
        float l = vec3_length(n);

        CHECK(l == doctest::Approx(1.0f));
    }

    SUBCASE("Case 03")
    {
        Vec4 v  = Vec4{2.0f, 4.0f, 6.0f, 8.0f};
        Vec4 n  = vec4_normalize(v);
        float l = vec4_length(n);

        CHECK(l == doctest::Approx(1.0f));
    }
}

TEST_CASE("[ankh-math]: vector dot")
{

    SUBCASE("Case 01")
    {
        Vec2 a = Vec2{1.0f, 2.0f};
        Vec2 b = Vec2{3.0f, 4.0f};

        float d = vec2_dot(a, b);

        CHECK(d == 11);
    }

    SUBCASE("Case 02")
    {
        Vec3 a = Vec3{1.0f, 2.0f, 3.0f};
        Vec3 b = Vec3{4.0f, 5.0f, 6.0f};

        float d = vec3_dot(a, b);

        CHECK(d == 32);
    }

    SUBCASE("Case 03")
    {
        Vec4 a = Vec4{1.0f, 2.0f, 3.0f, 4.0f};
        Vec4 b = Vec4{5.0f, 6.0f, 7.0f, 8.0f};

        float d = vec4_dot(a, b);

        CHECK(d == 70);
    }
}

TEST_CASE("[ankh-math]: vector cross")
{
    SUBCASE("Case 01")
    {
        Vec2 a = Vec2{1.0f, 0.0f};
        Vec2 b = Vec2{0.0f, 1.0f};

        float c = vec2_cross(a, b);

        CHECK(c == doctest::Approx(1));
    }

    SUBCASE("Case 02")
    {
        Vec2 a = Vec2{0.0f, 1.0f};
        Vec2 b = Vec2{1.0f, 0.0f};

        float c = vec2_cross(a, b);

        CHECK(c == doctest::Approx(-1));
    }

    SUBCASE("Case 03")
    {
        Vec3 a = Vec3{1.0f, 0.0f, 0.0f};
        Vec3 b = Vec3{0.0f, 1.0f, 0.0f};

        Vec3 c = vec3_cross(a, b);

        CHECK(c.x == doctest::Approx(0));
        CHECK(c.y == doctest::Approx(0));
        CHECK(c.z == doctest::Approx(1));
    }

    SUBCASE("Case 04")
    {
        Vec3 a = Vec3{0.0f, 1.0f, 0.0f};
        Vec3 b = Vec3{1.0f, 0.0f, 0.0f};

        Vec3 c = vec3_cross(a, b);

        CHECK(c.x == doctest::Approx(0));
        CHECK(c.y == doctest::Approx(0));
        CHECK(c.z == doctest::Approx(-1));
    }

    SUBCASE("Case 05")
    {
        Vec3 a = Vec3{0.0f, 1.0f, 0.0f};
        Vec3 b = Vec3{0.0f, 0.0f, 1.0f};

        Vec3 c = vec3_cross(a, b);

        CHECK(c.x == doctest::Approx(1));
        CHECK(c.y == doctest::Approx(0));
        CHECK(c.z == doctest::Approx(0));
    }

    SUBCASE("Case 06")
    {
        Vec3 a = Vec3{0.0f, 0.0f, 1.0f};
        Vec3 b = Vec3{0.0f, 1.0f, 0.0f};

        Vec3 c = vec3_cross(a, b);

        CHECK(c.x == doctest::Approx(-1));
        CHECK(c.y == doctest::Approx(0));
        CHECK(c.z == doctest::Approx(0));
    }

    SUBCASE("Case 07")
    {
        Vec3 a = Vec3{0.0f, 0.0f, 1.0f};
        Vec3 b = Vec3{1.0f, 0.0f, 0.0f};

        Vec3 c = vec3_cross(a, b);

        CHECK(c.x == doctest::Approx(0));
        CHECK(c.y == doctest::Approx(1));
        CHECK(c.z == doctest::Approx(0));
    }

    SUBCASE("Case 08")
    {
        Vec3 a = Vec3{1.0f, 0.0f, 0.0f};
        Vec3 b = Vec3{0.0f, 0.0f, 1.0f};

        Vec3 c = vec3_cross(a, b);

        CHECK(c.x == doctest::Approx(0));
        CHECK(c.y == doctest::Approx(-1));
        CHECK(c.z == doctest::Approx(0));
    }
}

TEST_CASE("[ankh-math]: matrix creation && at operator")
{
    SUBCASE("Case 01")
    {
        Mat2 A = Mat2{};
        Mat2 B = Mat2{
             1, 2,
             3, 4};

        for(int i = 0; i < 4; ++i)
            CHECK(mat2_at(A, i) == 0);

        for (int i = 0; i < 4; ++i)
            CHECK(mat2_at(B, i) == i + 1);
    }

    SUBCASE("Case 02")
    {
        Mat3 A = Mat3{};
        Mat3 B = Mat3{
             1, 2, 3,
             4, 5, 6,
             7, 8, 9};

        for(int i = 0; i < 9; ++i)
            CHECK(mat3_at(A, i) == 0);

        for (int i = 0; i < 9; ++i)
            CHECK(mat3_at(B, i) == i + 1);
    }
    SUBCASE("Case 03")
    {
        Mat4 A = Mat4{};
        Mat4 B = Mat4{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,
            13, 14, 15, 16};

        for(int i = 0; i < 16; ++i)
            CHECK(mat4_at(A, i) == 0);

        for (int i = 0; i < 16; ++i)
            CHECK(mat4_at(B, i) == i + 1);
    }
}

TEST_CASE("[ankh-math]: matrix addition")
{
    SUBCASE("Case 01")
    {
        Mat2 A = Mat2{
            11, 12,
            13, 14};

        Mat2 B = Mat2{
            15, 16,
            17, 18};

        Mat2 C = A + B;

        for (int i = 0; i < 4; ++i)
            CHECK(mat2_at(C, i) == mat2_at(A, i) + mat2_at(B, i));
    }
    SUBCASE("Case 02")
    {
        Mat2 A = Mat2{
            11, 12,
            13, 14};

        Mat2 B = Mat2{
            15, 16,
            17, 18};

        Mat2 C = A;
        C += B;

        for (int i = 0; i < 4; ++i)
            CHECK(mat2_at(C, i) == mat2_at(A, i) + mat2_at(B, i));
    }

    SUBCASE("Case 03")
    {
        Mat3 A = Mat3{
            11, 12, 13,
            14, 15, 16,
            17, 18, 19};

        Mat3 B = Mat3{
            20, 21, 22,
            23, 24, 25,
            26, 27, 28};

        Mat3 C = A + B;

        for (int i = 0; i < 9; ++i)
            CHECK(mat3_at(C, i) == mat3_at(A, i) + mat3_at(B, i));
    }
    SUBCASE("Case 04")
    {
        Mat3 A = Mat3{
            11, 12, 13,
            14, 15, 16,
            17, 18, 19};

        Mat3 B = Mat3{
            20, 21, 22,
            23, 24, 25,
            26, 27, 28};

        Mat3 C = A;
        C += B;

        for (int i = 0; i < 9; ++i)
            CHECK(mat3_at(C, i) == mat3_at(A, i) + mat3_at(B, i));
    }

    SUBCASE("Case 05")
    {
        Mat4 A = Mat4{
            11, 12, 13, 14,
            15, 16, 17, 18,
            19, 20, 21, 22,
            23, 24, 25, 26};

        Mat4 B = Mat4{
            27, 28, 29, 30,
            31, 32, 33, 34,
            35, 36, 37, 38,
            39, 40, 41, 42};

        Mat4 C = A + B;

        for (int i = 0; i < 16; ++i)
            CHECK(mat4_at(C, i) == mat4_at(A, i) + mat4_at(B, i));
    }
    SUBCASE("Case 06")
    {
        Mat4 A = Mat4{
            11, 12, 13, 14,
            15, 16, 17, 18,
            19, 20, 21, 22,
            23, 24, 25, 26};

        Mat4 B = Mat4{
            27, 28, 29, 30,
            31, 32, 33, 34,
            35, 36, 37, 38,
            39, 40, 41, 42};

        Mat4 C = A;
        C += B;

        for (int i = 0; i < 16; ++i)
            CHECK(mat4_at(C, i) == mat4_at(A, i) + mat4_at(B, i));
    }
}

TEST_CASE("[ank-math]: matrix unary")
{
    SUBCASE("Case 01")
    {
        Mat2 A = Mat2{
            11, 12,
            13, 14};

        Mat2 B = -A;

        for (int i = 0; i < 4; ++i)
            CHECK(mat2_at(B, i) == -mat2_at(A, i));
    }

    SUBCASE("Case 02")
    {
        Mat3 A = Mat3{
            11, 12, 13,
            14, 15, 16,
            17, 18, 19};

        Mat3 B = -A;

        for (int i = 0; i < 9; ++i)
            CHECK(mat3_at(B, i) == -mat3_at(A, i));
    }

    SUBCASE("Case 03")
    {
        Mat4 A = Mat4{
            11, 12, 13, 14,
            15, 16, 17, 18,
            19, 20, 21, 22,
            23, 24, 25, 26};

        Mat4 B = -A;

        for (int i = 0; i < 16; ++i)
            CHECK(mat4_at(B, i) == -mat4_at(A, i));
    }
}

TEST_CASE("[ankh-math]: matrix subtraction")
{
    SUBCASE("Case 01")
    {
        Mat2 A = Mat2{
            11, 12,
            13, 14};

        Mat2 B = Mat2{
            15, 16,
            17, 18};

        Mat2 C = A - B;

        for (int i = 0; i < 4; ++i)
            CHECK(mat2_at(C, i) == mat2_at(A, i) - mat2_at(B, i));
    }
    SUBCASE("Case 02")
    {
        Mat2 A = Mat2{
            11, 12,
            13, 14};

        Mat2 B = Mat2{
            15, 16,
            17, 18};

        Mat2 C = A;
        C -= B;

        for (int i = 0; i < 4; ++i)
            CHECK(mat2_at(C, i) == mat2_at(A, i) - mat2_at(B, i));
    }

    SUBCASE("Case 03")
    {
        Mat3 A = Mat3{
            11, 12, 13,
            14, 15, 16,
            17, 18, 19};

        Mat3 B = Mat3{
            20, 21, 22,
            23, 24, 25,
            26, 27, 28};

        Mat3 C = A - B;

        for (int i = 0; i < 9; ++i)
            CHECK(mat3_at(C, i) == mat3_at(A, i) - mat3_at(B, i));
    }
    SUBCASE("Case 04")
    {
        Mat3 A = Mat3{
            11, 12, 13,
            14, 15, 16,
            17, 18, 19};

        Mat3 B = Mat3{
            20, 21, 22,
            23, 24, 25,
            26, 27, 28};

        Mat3 C = A;
        C -= B;

        for (int i = 0; i < 9; ++i)
            CHECK(mat3_at(C, i) == mat3_at(A, i) - mat3_at(B, i));
    }

    SUBCASE("Case 05")
    {
        Mat4 A = Mat4{
            11, 12, 13, 14,
            15, 16, 17, 18,
            19, 20, 21, 22,
            23, 24, 25, 26};

        Mat4 B = Mat4{
            27, 28, 29, 30,
            31, 32, 33, 34,
            35, 36, 37, 38,
            39, 40, 41, 42};

        Mat4 C = A - B;

        for (int i = 0; i < 16; ++i)
            CHECK(mat4_at(C, i) == mat4_at(A, i) - mat4_at(B, i));
    }
    SUBCASE("Case 06")
    {
        Mat4 A = Mat4{
            11, 12, 13, 14,
            15, 16, 17, 18,
            19, 20, 21, 22,
            23, 24, 25, 26};

        Mat4 B = Mat4{
            27, 28, 29, 30,
            31, 32, 33, 34,
            35, 36, 37, 38,
            39, 40, 41, 42};

        Mat4 C = A;
        C -= B;

        for (int i = 0; i < 16; ++i)
            CHECK(mat4_at(C, i) == mat4_at(A, i) - mat4_at(B, i));
    }
}

TEST_CASE("[ankh-math]: matrix scalar multiplication")
{
    SUBCASE("Case 01")
    {
        Mat2 A = Mat2{
            11, 12,
            13, 14};

        float f = 6.0f;
        Mat2 B = A * f;
        Mat2 C = f * A;

        for (int i = 0; i < 4; ++i)
        {
            CHECK(mat2_at(B, i) == mat2_at(A, i) * f);
            CHECK(mat2_at(C, i) == mat2_at(A, i) * f);
            CHECK(mat2_at(C, i) == mat2_at(B, i));
        }
    }

    SUBCASE("Case 02")
    {
        Mat3 A = Mat3{
            11, 12, 13,
            14, 15, 16,
            17, 18, 19};

        float f = 6.0f;
        Mat3 B = A * f;
        Mat3 C = f * A;

        for (int i = 0; i < 9; ++i)
        {
            CHECK(mat3_at(B, i) == mat3_at(A, i) * f);
            CHECK(mat3_at(C, i) == mat3_at(A, i) * f);
            CHECK(mat3_at(C, i) == mat3_at(B, i));
        }
    }

    SUBCASE("Case 03")
    {
        Mat4 A = Mat4{
            11, 12, 13, 14,
            15, 16, 17, 18,
            19, 20, 21, 22,
            23, 24, 25, 26};

        float f = 6.0f;
        Mat4 B = A * f;
        Mat4 C = f * A;

        for (int i = 0; i < 16; ++i)
        {
            CHECK(mat4_at(B, i) == mat4_at(A, i) * f);
            CHECK(mat4_at(C, i) == mat4_at(A, i) * f);
            CHECK(mat4_at(C, i) == mat4_at(B, i));
        }
    }
}

TEST_CASE("[ankh-math]: matrix vector multiplication")
{
    SUBCASE("Case 01")
    {
        Vec2 a = Vec2{1, 2};

        Mat2 M = Mat2{
            11, 12,
            13, 14};

        Vec2 r = Vec2{37, 40};

        Vec2 b = a * M;

        CHECK(b.x == r.x);
        CHECK(b.y == r.y);
    }

    SUBCASE("Case 02")
    {
        Vec3 a = Vec3{1, 2, 3};

        Mat3 M = Mat3{
            11, 12, 13,
            14, 15, 16,
            17, 18, 19};

        Vec3 r = Vec3{90, 96, 102};

        Vec3 b = a * M;

        CHECK(b.x == r.x);
        CHECK(b.y == r.y);
        CHECK(b.z == r.z);
    }

    SUBCASE("Case 03")
    {
        Vec4 a = Vec4{1, 2, 3, 4};

        Mat4 M = Mat4{
            11, 12, 13, 14,
            15, 16, 17, 18,
            19, 20, 21, 22,
            23, 24, 25, 26};

        Vec4 r = Vec4{190, 200, 210, 220};

        Vec4 b = a * M;

        CHECK(b.x == r.x);
        CHECK(b.y == r.y);
        CHECK(b.z == r.z);
        CHECK(b.w == r.w);
    }
}

TEST_CASE("[ankh-math]: matrix matrix multiplication")
{
    SUBCASE("Case 01")
    {
        Mat2 A = Mat2{
            11, 12,
            13, 14};

        Mat2 B = Mat2{
            15, 16,
            17, 18};

        Mat2 R = Mat2{
            369, 392,
            433, 460};

        Mat2 C = A * B;

        for (int i = 0; i < 4; ++i)
            CHECK(mat2_at(C, i) == mat2_at(R, i));
    }

    SUBCASE("Case 02")
    {
        Mat3 A = Mat3{
            11, 12, 13,
            14, 15, 16,
            17, 18, 19};

        Mat3 B = Mat3{
            20, 21, 22,
            23, 24, 25,
            26, 27, 28};

        Mat3 R = Mat3{
             834,  870,  906,
            1041, 1086, 1131,
            1248, 1302, 1356};

        Mat3 C = A * B;

        for (int i = 0; i < 9; ++i)
            CHECK(mat3_at(C, i) == mat3_at(R, i));
    }

    SUBCASE("Case 03")
    {
        Mat4 A = Mat4{
            11, 12, 13, 14,
            15, 16, 17, 18,
            19, 20, 21, 22,
            23, 24, 25, 26};

        Mat4 B = Mat4{
            27, 28, 29, 30,
            31, 32, 33, 34,
            35, 36, 37, 38,
            39, 40, 41, 42};

        Mat4 R = Mat4{
            1670, 1720, 1770, 1820,
            2198, 2264, 2330, 2396,
            2726, 2808, 2890, 2972,
            3254, 3352, 3450, 3548};

        Mat4 C = A * B;

        for (int i = 0; i < 16; ++i)
            CHECK(mat4_at(C, i) == mat4_at(R, i));
    }
}

TEST_CASE("[ankh-math]: matrix scalar division")
{
    SUBCASE("Case 01")
    {
        Mat2 A = Mat2{
            11, 12,
            13, 14};

        float f = 6.0f;
        Mat2 B = A / f;

        for (int i = 0; i < 4; ++i)
            CHECK(mat2_at(B, i) == mat2_at(A, i) / f);
    }

    SUBCASE("Case 02")
    {
        Mat3 A = Mat3{
            11, 12, 13,
            14, 15, 16,
            17, 18, 19};

        float f = 6.0f;
        Mat3 B = A / f;

        for (int i = 0; i < 9; ++i)
            CHECK(mat3_at(B, i) == mat3_at(A, i) / f);
    }

    SUBCASE("Case 03")
    {
        Mat4 A = Mat4{
            11, 12, 13, 14,
            15, 16, 17, 18,
            19, 20, 21, 22,
            23, 24, 25, 26};

        float f = 6.0f;
        Mat4 B = A / f;

        for (int i = 0; i < 16; ++i)
            CHECK(mat4_at(B, i) == mat4_at(A, i) / f);
    }
}

TEST_CASE("[ankh-math]: matrix identity")
{
    SUBCASE("Case 01")
    {
        Mat2 M = mat2_identity();

        CHECK(M.m00 == 1);
        CHECK(M.m01 == 0);

        CHECK(M.m10 == 0);
        CHECK(M.m11 == 1);
    }

    SUBCASE("Case 02")
    {
        Mat3 M = mat3_identity();

        CHECK(M.m00 == 1);
        CHECK(M.m01 == 0);
        CHECK(M.m02 == 0);

        CHECK(M.m10 == 0);
        CHECK(M.m11 == 1);
        CHECK(M.m12 == 0);

        CHECK(M.m20 == 0);
        CHECK(M.m21 == 0);
        CHECK(M.m22 == 1);
    }

    SUBCASE("Case 03")
    {
        Mat4 M = mat4_identity();

        CHECK(M.m00 == 1);
        CHECK(M.m01 == 0);
        CHECK(M.m02 == 0);
        CHECK(M.m03 == 0);

        CHECK(M.m10 == 0);
        CHECK(M.m11 == 1);
        CHECK(M.m12 == 0);
        CHECK(M.m13 == 0);

        CHECK(M.m20 == 0);
        CHECK(M.m21 == 0);
        CHECK(M.m22 == 1);
        CHECK(M.m23 == 0);

        CHECK(M.m30 == 0);
        CHECK(M.m31 == 0);
        CHECK(M.m32 == 0);
        CHECK(M.m33 == 1);
    }
}

TEST_CASE("[ankh-math]: matrix transpose")
{
    SUBCASE("Case 01")
    {
        Mat2 A = Mat2{
             1,  3,
             2,  4};

        Mat2 B = mat2_transpose(A);

        for (int i = 0; i < 4; ++i)
            CHECK(mat2_at(B, i) == i + 1);
    }

    SUBCASE("Case 02")
    {
        Mat3 A = Mat3{
             1,  4, 7,
             2,  5, 8,
             3,  6, 9};

        Mat3 B = mat3_transpose(A);

        for (int i = 0; i < 9; ++i)
            CHECK(mat3_at(B, i) == i + 1);
    }

    SUBCASE("Case 03")
    {
        Mat4 A = Mat4{
             1,  5,  9, 13,
             2,  6, 10, 14,
             3,  7, 11, 15,
             4,  8, 12, 16};

        Mat4 B = mat4_transpose(A);

        for (int i = 0; i < 16; ++i)
            CHECK(mat4_at(B, i) == i + 1);
    }
}

TEST_CASE("[ankh-math]: matrix det")
{
    SUBCASE("Case 01")
    {
        Mat2 I = mat2_identity();

        float d = mat2_det(I);

        CHECK(d == 1.0f);
    }
    SUBCASE("Case 02")
    {
        Mat2 M = Mat2{
             1,  2,
             3,  4};

        float d = mat2_det(M);

        CHECK(d == -2);
    }

    SUBCASE("Case 03")
    {
        Mat3 I = mat3_identity();

        float d = mat3_det(I);

        CHECK(d == 1.0f);
    }
    SUBCASE("Case 04")
    {
        Mat3 M = Mat3{
             3,  2, -1,
             2,  1,  5,
             0,  5,  2};

        float d = mat3_det(M);

        CHECK(d == -87);
    }
    SUBCASE("Case 05")
    {
        Mat3 M = Mat3{
            11, 12, 13,
            14, 15, 16,
            17, 18, 19};

        float d = mat3_det(M);

        CHECK(d == 0.0f);
    }

    SUBCASE("Case 06")
    {
        Mat4 I = mat4_identity();

        float d = mat4_det(I);

        CHECK(d == 1.0f);
    }
    SUBCASE("Case 07")
    {
        Mat4 M = Mat4{
             3,  2, -1,  4,
             2,  1,  5,  7,
             0,  5,  2, -6,
            -1,  2,  1,  0};

        float d = mat4_det(M);

        CHECK(d == -418);
    }
    SUBCASE("Case 08")
    {
        Mat4 M = Mat4{
            11, 12, 13, 14,
            15, 16, 17, 18,
            19, 20, 21, 22,
            23, 24, 25, 26};

        float d = mat4_det(M);

        CHECK(d == 0.0f);
    }
}

TEST_CASE("[ankh-math]: matrix is invertible")
{
    SUBCASE("Case 01")
    {
        Mat2 M = Mat2{
            2, 5,
            1, 4};

        bool invertible = mat2_invertible(M);

        CHECK(invertible == true);
    }
    SUBCASE("Case 02")
    {
        Mat2 M = Mat2{
            1, 1,
            1, 1};

        bool invertible = mat2_invertible(M);

        CHECK(invertible == false);
    }

    SUBCASE("Case 03")
    {
        Mat3 M = Mat3{
            2, 5, 0,
            1, 4, 2,
            7, 8, 8};

        bool invertible = mat3_invertible(M);

        CHECK(invertible == true);
    }
    SUBCASE("Case 04")
    {
        Mat3 M = Mat3{
             1,  2,  0,
             3, -1,  2,
            -2,  3, -2};

        bool invertible = mat3_invertible(M);

        CHECK(invertible == false);
    }

    SUBCASE("Case 05")
    {
        Mat4 M = Mat4{
            2, 5, 0, 8,
            1, 4, 2, 6,
            7, 8, 8, 3,
            1, 5, 7 ,8};

        bool invertible = mat4_invertible(M);

        CHECK(invertible == true);
    }
    SUBCASE("Case 06")
    {
        Mat4 M = Mat4{
            16,  2,  3, 13,
             5, 11, 10,  8,
             9,  7,  6, 12,
             4, 14, 15,  1};

        bool invertible = mat4_invertible(M);

        CHECK(invertible == false);
    }
}

TEST_CASE("[ankh-math]: matrix inverse")
{
    SUBCASE("Case 01")
    {
        Mat2 A = Mat2{
            2, 5,
            1, 4};

        Mat2 B = mat2_inverse(A);

        Mat2 C = A * B;

        CHECK(C.m00 == doctest::Approx(1.0f));
        CHECK(C.m01 == doctest::Approx(0.0f));

        CHECK(C.m10 == doctest::Approx(0.0f));
        CHECK(C.m11 == doctest::Approx(1.0f));
    }
    SUBCASE("Case 02")
    {
        Mat2 A = Mat2{
             0.871214f,  0.000000f,
            -0.192902f,  0.919559f};

        Vec2 a = Vec2{1, 2};

        Mat2 B = mat2_inverse(A);

        Vec2 b = a * A;

        Vec2 c = b * B;

        CHECK(c.x == doctest::Approx(a.x));
        CHECK(c.y == doctest::Approx(a.y));
    }

    SUBCASE("Case 03")
    {
        Mat3 A = Mat3{
            2, 5, 0,
            1, 4, 2,
            7, 8, 8};

        Mat3 B = mat3_inverse(A);

        Mat3 C = A * B;

        CHECK(C.m00 == doctest::Approx(1.0f));
        CHECK(C.m01 == doctest::Approx(0.0f));
        CHECK(C.m02 == doctest::Approx(0.0f));

        CHECK(C.m10 == doctest::Approx(0.0f));
        CHECK(C.m11 == doctest::Approx(1.0f));
        CHECK(C.m12 == doctest::Approx(0.0f));

        CHECK(C.m20 == doctest::Approx(0.0f));
        CHECK(C.m21 == doctest::Approx(0.0f));
        CHECK(C.m22 == doctest::Approx(1.0f));
    }
    SUBCASE("Case 04")
    {
        Mat3 A = Mat3{
             0.871214f,  0.000000f, -0.490904f,
            -0.192902f,  0.919559f, -0.342346f,
             0.451415f,  0.392953f,  0.801132f};

        Vec3 a = Vec3{1, 2, 3};

        Mat3 B = mat3_inverse(A);

        Vec3 b = a * A;

        Vec3 c = b * B;

        CHECK(c.x == doctest::Approx(a.x));
        CHECK(c.y == doctest::Approx(a.y));
        CHECK(c.z == doctest::Approx(a.z));
    }

    SUBCASE("Case 05")
    {
        Mat4 A = Mat4{
            2, 5, 0, 8,
            1, 4, 2, 6,
            7, 8, 8, 3,
            1, 5, 7 ,8};

        Mat4 B = mat4_inverse(A);

        Mat4 C = A * B;

        CHECK(C.m00 == doctest::Approx(1.0f));
        CHECK(C.m01 == doctest::Approx(0.0f));
        CHECK(C.m02 == doctest::Approx(0.0f));
        CHECK(C.m03 == doctest::Approx(0.0f));

        CHECK(C.m10 == doctest::Approx(0.0f));
        CHECK(C.m11 == doctest::Approx(1.0f));
        CHECK(C.m12 == doctest::Approx(0.0f));
        CHECK(C.m13 == doctest::Approx(0.0f));

        CHECK(C.m20 == doctest::Approx(0.0f));
        CHECK(C.m21 == doctest::Approx(0.0f));
        CHECK(C.m22 == doctest::Approx(1.0f));
        CHECK(C.m23 == doctest::Approx(0.0f));

        CHECK(C.m30 == doctest::Approx(0.0f));
        CHECK(C.m31 == doctest::Approx(0.0f));
        CHECK(C.m32 == doctest::Approx(0.0f));
        CHECK(C.m33 == doctest::Approx(1.0f));
    }
    SUBCASE("Case 06")
    {
        Mat4 A = Mat4{
             0.871214f,  0.000000f, -0.490904f, 0.0f,
            -0.192902f,  0.919559f, -0.342346f, 0.0f,
             0.451415f,  0.392953f,  0.801132f, 0.0f,
            14.777467f, 29.361945f, 27.993464f, 1.0f};

        Vec4 a = Vec4{1, 2, 3, 1};

        Mat4 B = mat4_inverse(A);

        Vec4 b = a * A;

        Vec4 c = b * B;

        CHECK(c.x == doctest::Approx(a.x));
        CHECK(c.y == doctest::Approx(a.y));
        CHECK(c.z == doctest::Approx(a.z));
        CHECK(c.w == doctest::Approx(a.w));
    }
}

TEST_CASE("[ankh-math]: matrix axis")
{
    SUBCASE("Case 01")
    {
        Mat2 M = Mat2{
             0.6f, 0.8f,
            -0.8f, 0.6f};

        Vec2 axis_x = mat2_axis_x(M);
        Vec2 axis_y = mat2_axis_y(M);

        CHECK(axis_x.x == doctest::Approx(0.6f));
        CHECK(axis_x.y == doctest::Approx(0.8f));

        CHECK(axis_y.x == doctest::Approx(-0.8f));
        CHECK(axis_y.y == doctest::Approx(0.6f));
    }

    SUBCASE("Case 02")
    {
        Mat3 M = Mat3{
             0.6f, 0.8f, 0.0f,
            -0.8f, 0.6f, 0.0f,
             0.0f, 0.0f, 1.0f};

        Vec3 axis_x = mat3_axis_x(M);
        Vec3 axis_y = mat3_axis_y(M);
        Vec3 axis_z = mat3_axis_z(M);

        CHECK(axis_x.x == doctest::Approx(0.6f));
        CHECK(axis_x.y == doctest::Approx(0.8f));
        CHECK(axis_x.z == doctest::Approx(0.0f));

        CHECK(axis_y.x == doctest::Approx(-0.8f));
        CHECK(axis_y.y == doctest::Approx(0.6f));
        CHECK(axis_y.z == doctest::Approx(0.0f));

        CHECK(axis_z.x == doctest::Approx(0.0f));
        CHECK(axis_z.y == doctest::Approx(0.0f));
        CHECK(axis_z.z == doctest::Approx(1.0f));
    }

    SUBCASE("Case 03")
    {
        Mat4 M = Mat4{
             0.6f, 0.8f, 0.0f, 0.0f,
            -0.8f, 0.6f, 0.0f, 0.0f,
             0.0f, 0.0f, 1.0f, 0.0f,
             0.0f, 0.0f, 0.0f, 1.0f};

        Vec3 axis_x = mat4_axis_x(M);
        Vec3 axis_y = mat4_axis_y(M);
        Vec3 axis_z = mat4_axis_z(M);

        CHECK(axis_x.x == doctest::Approx(0.6f));
        CHECK(axis_x.y == doctest::Approx(0.8f));
        CHECK(axis_x.z == doctest::Approx(0.0f));

        CHECK(axis_y.x == doctest::Approx(-0.8f));
        CHECK(axis_y.y == doctest::Approx(0.6f));
        CHECK(axis_y.z == doctest::Approx(0.0f));

        CHECK(axis_z.x == doctest::Approx(0.0f));
        CHECK(axis_z.y == doctest::Approx(0.0f));
        CHECK(axis_z.z == doctest::Approx(1.0f));
    }
}

TEST_CASE("[ankh-math]: translation matrix")
{
    SUBCASE("Case 01")
    {
        Mat3 M = mat3_translation_2d(10, 20);

        Vec3 a = Vec3{1, 2, 1};

        Vec3 b = a * M;

        CHECK(b.x == doctest::Approx(11));
        CHECK(b.y == doctest::Approx(22));
        CHECK(b.z == doctest::Approx(1));
    }

    SUBCASE("Case 02")
    {
        Mat4 M = mat4_translation(10, 20, 30);

        Vec4 a = Vec4{1, 2, 3, 1};

        Vec4 b = a * M;

        CHECK(b.x == doctest::Approx(11));
        CHECK(b.y == doctest::Approx(22));
        CHECK(b.z == doctest::Approx(33));
        CHECK(b.w == doctest::Approx(1));
    }
}

TEST_CASE("[ankh-math]: rotation matrix")
{
    SUBCASE("Case 01")
    {
        Mat2 A = mat2_rotation(PI_OVER_2);

        Vec2 a = Vec2{1, 1};

        Vec2 b = a * A;

        CHECK(b.x == doctest::Approx(-a.x));
        CHECK(b.y == doctest::Approx(a.y));

        Mat2 B = mat2_rotation(-PI_OVER_2);

        Vec2 c = b * B;

        CHECK(c.x == doctest::Approx(a.x));
        CHECK(c.y == doctest::Approx(a.y));
    }

    SUBCASE("Case 02")
    {
        Mat3 A = mat3_rotation_2d(PI_OVER_2);

        Vec3 a = Vec3{1, 1, 1};

        Vec3 b = a * A;

        CHECK(b.x == doctest::Approx(-a.x));
        CHECK(b.y == doctest::Approx(a.y));
        CHECK(b.z == doctest::Approx(1.0f));

        Mat3 B = mat3_rotation_2d(-PI_OVER_2);

        Vec3 c = b * B;

        CHECK(c.x == doctest::Approx(a.x));
        CHECK(c.y == doctest::Approx(a.y));
        CHECK(c.z == doctest::Approx(1.0f));
    }
    SUBCASE("Case 03")
    {
        Mat3 A = mat3_rotation_x(PI_OVER_2);

        Vec3 a = Vec3{1, 1, 1};

        Vec3 b = a * A;

        CHECK(b.x == doctest::Approx(a.x));
        CHECK(b.y == doctest::Approx(-a.y));
        CHECK(b.z == doctest::Approx(a.z));

        Mat3 B = mat3_rotation_x(-PI_OVER_2);

        Vec3 c = b * B;

        CHECK(c.x == doctest::Approx(a.x));
        CHECK(c.y == doctest::Approx(a.y));
        CHECK(c.z == doctest::Approx(a.z));
    }
    SUBCASE("Case 04")
    {
        Mat3 A = mat3_rotation_y(PI_OVER_2);

        Vec3 a = Vec3{1, 1, 1};

        Vec3 b = a * A;

        CHECK(b.x == doctest::Approx(a.x));
        CHECK(b.y == doctest::Approx(a.y));
        CHECK(b.z == doctest::Approx(-a.z));

        Mat3 B = mat3_rotation_y(-PI_OVER_2);

        Vec3 c = b * B;

        CHECK(c.x == doctest::Approx(a.x));
        CHECK(c.y == doctest::Approx(a.y));
        CHECK(c.z == doctest::Approx(a.z));
    }
    SUBCASE("Case 05")
    {
        Mat3 A = mat3_rotation_z(PI_OVER_2);

        Vec3 a = Vec3{1, 1, 1};

        Vec3 b = a * A;

        CHECK(b.x == doctest::Approx(-a.x));
        CHECK(b.y == doctest::Approx(a.y));
        CHECK(b.z == doctest::Approx(a.z));

        Mat3 B = mat3_rotation_z(-PI_OVER_2);

        Vec3 c = b * B;

        CHECK(c.x == doctest::Approx(a.x));
        CHECK(c.y == doctest::Approx(a.y));
        CHECK(c.z == doctest::Approx(a.z));
    }

    SUBCASE("Case 06")
    {
        Mat4 A = mat4_rotation_x(PI_OVER_2);

        Vec4 a = Vec4{1, 1, 1, 1};

        Vec4 b = a * A;

        CHECK(b.x == doctest::Approx(a.x));
        CHECK(b.y == doctest::Approx(-a.y));
        CHECK(b.z == doctest::Approx(a.z));

        Mat4 B = mat4_rotation_x(-PI_OVER_2);

        Vec4 c = b * B;

        CHECK(c.x == doctest::Approx(a.x));
        CHECK(c.y == doctest::Approx(a.y));
        CHECK(c.z == doctest::Approx(a.z));
    }
    SUBCASE("Case 07")
    {
        Mat4 A = mat4_rotation_y(PI_OVER_2);

        Vec4 a = Vec4{1, 1, 1, 1};

        Vec4 b = a * A;

        CHECK(b.x == doctest::Approx(a.x));
        CHECK(b.y == doctest::Approx(a.y));
        CHECK(b.z == doctest::Approx(-a.z));

        Mat4 B = mat4_rotation_y(-PI_OVER_2);

        Vec4 c = b * B;

        CHECK(c.x == doctest::Approx(a.x));
        CHECK(c.y == doctest::Approx(a.y));
        CHECK(c.z == doctest::Approx(a.z));
    }
    SUBCASE("Case 08")
    {
        Mat4 A = mat4_rotation_z(PI_OVER_2);

        Vec4 a = Vec4{1, 1, 1, 1};

        Vec4 b = a * A;

        CHECK(b.x == doctest::Approx(-a.x));
        CHECK(b.y == doctest::Approx(a.y));
        CHECK(b.z == doctest::Approx(a.z));

        Mat4 B = mat4_rotation_z(-PI_OVER_2);

        Vec4 c = b * B;

        CHECK(c.x == doctest::Approx(a.x));
        CHECK(c.y == doctest::Approx(a.y));
        CHECK(c.z == doctest::Approx(a.z));
    }
}

TEST_CASE("[ankh-math]: scaling matrix")
{
    SUBCASE("Case 01")
    {
        Mat2 M = mat2_scaling(10, 20);

        Vec2 a = Vec2{1, 2};

        Vec2 b = a * M;

        CHECK(b.x == doctest::Approx(10));
        CHECK(b.y == doctest::Approx(40));
    }

    SUBCASE("Case 02")
    {
        Mat3 M = mat3_scaling(10, 20, 30);

        Vec3 a = Vec3{1, 2, 3};

        Vec3 b = a * M;

        CHECK(b.x == doctest::Approx(10));
        CHECK(b.y == doctest::Approx(40));
        CHECK(b.z == doctest::Approx(90));
    }

    SUBCASE("Case 03")
    {
        Mat3 M = mat3_scaling_2d(10, 20);

        Vec3 a = Vec3{1, 2, 1};

        Vec3 b = a * M;

        CHECK(b.x == doctest::Approx(10));
        CHECK(b.y == doctest::Approx(40));
        CHECK(b.z == doctest::Approx(1));
    }

    SUBCASE("Case 04")
    {
        Mat4 M = mat4_scaling(10, 20, 30);

        Vec4 a = Vec4{1, 2, 3, 1};

        Vec4 b = a * M;

        CHECK(b.x == doctest::Approx(10));
        CHECK(b.y == doctest::Approx(40));
        CHECK(b.z == doctest::Approx(90));
        CHECK(b.w == doctest::Approx(1));
    }
}

TEST_CASE("[ankh-math]: ray plane intersection")
{
    SUBCASE("Case 01")
    {
        Vec3 ray_origin = Vec3{10, 10, 10};
        Vec3 ray_dir    = Vec3{ 1,  0,  0};

        Vec3 plane_point  = Vec3{0, 0, 0};
        Vec3 plane_normal = Vec3{0, 1, 0};

        float t;
        int res = ray_plane_intersection(ray_origin, ray_dir, plane_point, plane_normal, t);

        CHECK(res == 0);
    }
    SUBCASE("Case 02")
    {
        Vec3 ray_origin = Vec3{10, 10, 10};
        Vec3 ray_dir    = Vec3{ 0,  1,  0};

        Vec3 plane_point  = Vec3{0, 0, 0};
        Vec3 plane_normal = Vec3{0, 1, 0};

        float t;
        int res = ray_plane_intersection(ray_origin, ray_dir, plane_point, plane_normal, t);

        CHECK(res == 1);
        CHECK(t == doctest::Approx(-10));
    }
    SUBCASE("Case 03")
    {
        Vec3 ray_origin = Vec3{10, 10, 10};
        Vec3 ray_dir    = Vec3{ 0,  1,  0};

        Vec3 plane_point  = Vec3{0,  0, 0};
        Vec3 plane_normal = Vec3{0, -1, 0};

        float t;
        int res = ray_plane_intersection(ray_origin, ray_dir, plane_point, plane_normal, t);

        CHECK(res == 1);
        CHECK(t == doctest::Approx(-10));
    }
    SUBCASE("Case 04")
    {
        Vec3 ray_origin = Vec3{10, 10, 10};
        Vec3 ray_dir    = Vec3{0,  -1,  0};

        Vec3 plane_point  = Vec3{0, 0, 0};
        Vec3 plane_normal = Vec3{0, 1, 0};

        float t;
        int res = ray_plane_intersection(ray_origin, ray_dir, plane_point, plane_normal, t);

        CHECK(res == 1);
        CHECK(t == doctest::Approx(10));
    }
    SUBCASE("Case 05")
    {
        Vec3 ray_origin = Vec3{0, 0, 0};
        Vec3 ray_dir    = Vec3{0, 1, 0};

        Vec3 plane_point  = Vec3{10, 10, 10};
        Vec3 plane_normal = Vec3{ 0,  1,  0};

        float t;
        int res = ray_plane_intersection(ray_origin, ray_dir, plane_point, plane_normal, t);

        CHECK(res == 1);
        CHECK(t == doctest::Approx(10));
    }
    SUBCASE("Case 06")
    {
        Vec3 ray_origin = Vec3{0, 0, 0};
        Vec3 ray_dir    = Vec3{0, 1, 0};

        Vec3 plane_point  = Vec3{10, 10, 10};
        Vec3 plane_normal = Vec3{ 0, -1,  0};

        float t;
        int res = ray_plane_intersection(ray_origin, ray_dir, plane_point, plane_normal, t);

        CHECK(res == 1);
        CHECK(t == doctest::Approx(10));
    }
    SUBCASE("Case 07")
    {
        Vec3 ray_origin = Vec3{0, 0, 0};
        Vec3 ray_dir    = Vec3{0, -1, 0};

        Vec3 plane_point  = Vec3{10, 10, 10};
        Vec3 plane_normal = Vec3{ 0,  1,  0};

        float t;
        int res = ray_plane_intersection(ray_origin, ray_dir, plane_point, plane_normal, t);

        CHECK(res == 1);
        CHECK(t == doctest::Approx(-10));
    }
    SUBCASE("Case 08")
    {
        Vec3 ray_origin = Vec3{5, 13, 2};
        Vec3 ray_dir    = vec3_normalize(Vec3{1, 1, 1});

        Vec3 plane_point  = Vec3{7, 20, 8};
        Vec3 plane_normal = vec3_normalize(Vec3{-1, -2, -3});

        float t;
        int res = ray_plane_intersection(ray_origin, ray_dir, plane_point, plane_normal, t);

        CHECK(res == 1);
        CHECK(t == doctest::Approx(9.81f).epsilon(0.01f));
    }
    SUBCASE("Case 09")
    {
        Vec3 ray_origin = Vec3{5, 13, 2};
        Vec3 ray_dir    = vec3_normalize(Vec3{-1, -1, -1});

        Vec3 plane_point  = Vec3{7, 20, 8};
        Vec3 plane_normal = vec3_normalize(Vec3{-1, -2, -3});

        float t;
        int res = ray_plane_intersection(ray_origin, ray_dir, plane_point, plane_normal, t);

        CHECK(res == 1);
        CHECK(t == doctest::Approx(-9.81f).epsilon(0.01f));
    }
}
