#pragma once

#include "math/sky_math_types.h"
#include "math/sky_math_vec3.h"
#include "math/sky_math_mat4.h"

struct Sky_Cam
{
    Vec3 position;
    Vec3 forward;

    float fov;
    float aspect;
    float znear;
    float zfar;
};

inline Mat4
sky_cam_view_mat(const Sky_Cam &cam)
{
    Vec3 up = Vec3{0.0f, 1.0f, 0.0f};
    Vec3 right = vec3_cross(up, cam.forward);
    up = vec3_cross(cam.forward, right);

    Mat4 res = mat4_coord(right, up, cam.forward);
    res.m30 = -cam.position.x;
    res.m31 = -cam.position.y;
    res.m32 = -cam.position.z;

    return res;
}

inline Mat4
sky_cam_proj_mat(const Sky_Cam &cam)
{
    return mat4_prespective(cam.fov * DEGREE_TO_RAD, cam.aspect, cam.znear, cam.zfar);
}

inline Mat4
sky_cam_viewproj_mat(const Sky_Cam &cam)
{
    return sky_cam_view_mat(cam) * sky_cam_proj_mat(cam);
}