#include "sky_terrain.h"
#include "sky_gfx.h"
#include "math/sky_math_vec3.h"

#include <stdlib.h>
#include <GL/glew.h>

Sky_Terrain
sky_terrain_generate(int width, int depth, int resolution_x, int resolution_z)
{
    Sky_Terrain self{};

    Vec3 start = Vec3{-(float)width / 2.0f, 0.0f, -(float)depth / 2.0f};
    Vec3 step  = Vec3{(float)width / (float)resolution_x, 0.0f, (float)depth / (float)resolution_z};

    self.pos_count = resolution_x * resolution_z * 6;
    self.pos_cpu = (Vec3 *)calloc(self.pos_count, sizeof(Vec3));
    self.width = width;
    self.depth = depth;
    self.res_x = resolution_x;
    self.res_z = resolution_z;

    int index = 0;
    for (int j = 0; j < resolution_z; ++j)
    {
        for (int i = 0; i < resolution_x; ++i)
        {
            float y_offset = (float)(rand() % 2);
            Vec3 bl = start + Vec3{i * step.x, y_offset, j * step.z};
            Vec3 br = start + Vec3{(i + 1) * step.x,  y_offset, j * step.z};
            Vec3 tl = start + Vec3{i * step.x,  y_offset, (j + 1) * step.z};
            Vec3 tr = start + Vec3{(i + 1) * step.x,  y_offset, (j + 1) * step.z};

            // bl, tl, tr
            self.pos_cpu[index++] = bl;
            self.pos_cpu[index++] = tl;
            self.pos_cpu[index++] = tr;
            // bl, tr, br
            self.pos_cpu[index++] = bl;
            self.pos_cpu[index++] = tr;
            self.pos_cpu[index++] = br;
        }
    }

    glGenVertexArrays(1, &self.mesh_gpu);
    glBindVertexArray(self.mesh_gpu);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, self.pos_count * sizeof(Vec3), self.pos_cpu, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), 0);
    glEnableVertexAttribArray(0);

    return self;
}