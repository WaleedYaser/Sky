#pragma once

#include "sky_input.h"
#include "math/sky_math_types.h"
#include "math/sky_math_vec3.h"
#include "math/sky_math_mat4.h"

struct Sky_Cam
{
    Vec3 position;
    // TODO(Waleed): use quaternion
    Vec3 rotation;
    Vec3 right;
    Vec3 up;
    Vec3 forward;

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

    self.right   = Vec3{1.0f, 0.0f, 0.0f};
    self.up      = Vec3{0.0f, 1.0f, 0.0f};

    self.forward.x = sky_sin(self.rotation.y * DEGREE_TO_RAD) * sky_cos(self.rotation.x * DEGREE_TO_RAD);
    self.forward.y = sky_sin(self.rotation.x * DEGREE_TO_RAD);
    self.forward.z = sky_cos(self.rotation.y * DEGREE_TO_RAD) * sky_cos(self.rotation.x * DEGREE_TO_RAD);
    self.forward = vec3_normalize(self.forward);

    self.fov = 45.0f;
    self.aspect = 1.0f;
    self.znear = 0.1f;
    self.zfar = 100.0f;

    return self;
}

inline void
sky_cam_update(Sky_Cam &self, const Sky_Input &input, float width, float height)
{
    static float mouse_sensitivity = 0.1f;

    self.aspect = width / height;

    if (input.keys[SKY_KEY_MOUSE_MIDDLE].down)
    {
        self = sky_cam_init();
        self.aspect = width / height;
    }
    if (input.keys[SKY_KEY_MOUSE_LEFT].down)
    {
        float x_offset = input.mouse_dx * mouse_sensitivity;
        float y_offset = input.mouse_dy * mouse_sensitivity;

        self.rotation.y += x_offset;
        self.rotation.x += y_offset;

        if (self.rotation.x > 89.0f)
            self.rotation.x = 89.0f;
        if (self.rotation.x < -89.0f)
            self.rotation.x = -89.0f;

        // TODO(Waleed): not perfect
        self.forward.x = sky_sin(self.rotation.y * DEGREE_TO_RAD) * sky_cos(self.rotation.x * DEGREE_TO_RAD);
        self.forward.y = sky_sin(self.rotation.x * DEGREE_TO_RAD);
        self.forward.z = sky_cos(self.rotation.y * DEGREE_TO_RAD) * sky_cos(self.rotation.x * DEGREE_TO_RAD);
        self.forward = vec3_normalize(self.forward);

        float d = vec3_dot(self.forward, self.up);
        if (d != 1.0f && d != -1.0f)
        {
            self.right = vec3_normalize(vec3_cross(self.up, self.forward));
            self.up = vec3_normalize(vec3_cross(self.forward, self.right));
        }
        else
        {
            self.up = vec3_normalize(vec3_cross(self.forward, self.right));
            self.right = vec3_normalize(vec3_cross(self.up, self.forward));
        }
    }
    if (input.keys[SKY_KEY_MOUSE_RIGHT].down)
    {
        float x_offset = input.mouse_dx * mouse_sensitivity;
        float y_offset = input.mouse_dy * mouse_sensitivity;

        self.position += x_offset * self.right;
        self.position -= y_offset * self.up;
    }
    if (input.mouse_wheel > 0)
        self.position -= self.forward;
    else if (input.mouse_wheel < 0)
        self.position += self.forward;
}

inline Mat4
sky_cam_view_mat(const Sky_Cam &self)
{
    return mat4_look_at(self.position, self.position - self.forward);
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