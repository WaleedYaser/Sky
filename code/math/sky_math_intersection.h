#pragma once

#include "sky_math_vec3.h"

inline int
ray_plane_intersection(
    Vec3 ray_origin, Vec3 ray_dir,
    Vec3 plane_point, Vec3 plane_normal,
    float &t)
{
    float d2 = vec3_dot(ray_dir, plane_normal);
    if (d2 == 0)
        return 0;

    float d1 = vec3_dot(plane_point - ray_origin, plane_normal);
    t = d1 / d2;

    return 1;
}

/* TODO
inline int
ray_aabb_intersection(
    Vec2 ray_origin, Vec2 ray_dir,
    Vec2 aabb_min, Vec2 aabb_max,
    float &t1, float&t2)
{

}

inline int
ray_aabb_intersection(
    Vec3 ray_origin, Vec3 ray_dir,
    Vec3 aabb_min, Vec3 aabb_max,
    float &t1, float&t2)
{

}

inline int
ray_sphere_intersection(
    Vec3 ray_origin, Vec3 ray_dir, Vec3 sphere_center, Vec3 sphere_radius, float &t1, float &t2)
{

}
*/