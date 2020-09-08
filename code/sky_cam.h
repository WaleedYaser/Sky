#pragma once

#include "math/sky_math_types.h"
#include "math/sky_math_vec3.h"
#include "math/sky_math_mat4.h"

struct Sky_Cam
{
    Vec3 position;
    Vec3 rotation;

    float fov;
    float aspect;
    float znear;
    float zfar;
};

inline Sky_Cam
sky_cam_init()
{
    Sky_Cam self{};

    self.position.z = 50.0f;
    self.position.y = 18.0f;
    self.rotation.x = 10.0f * DEGREE_TO_RAD;

    self.fov = 45.0f;
    self.aspect = 1.0f;
    self.znear = 0.1f;
    self.zfar = 100.0f;

    return self;
}

inline Mat4
sky_cam_view_mat(const Sky_Cam &self)
{
    return
        mat4_rotation_y(self.rotation.y) *
        mat4_translation(-self.position.x, -self.position.y, -self.position.z) *
        mat4_rotation_x(self.rotation.x);
}

inline Mat4
sky_cam_proj_mat(const Sky_Cam &self)
{
    return mat4_prespective(self.fov * DEGREE_TO_RAD, self.aspect, self.znear, self.zfar);
}

inline Mat4
sky_cam_viewproj_mat(const Sky_Cam &self)
{
    return sky_cam_view_mat(self) * sky_cam_proj_mat(self);
}