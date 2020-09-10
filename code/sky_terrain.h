#pragma once

#include "math/sky_math_types.h"

struct Sky_Terrain
{
    Vec3 *pos_cpu;
    int pos_count;
    unsigned int mesh_gpu;

    int width, depth;
    int res_x, res_z;
};

Sky_Terrain
sky_terrain_generate(int width, int depth, int resolution_x, int resolution_z);