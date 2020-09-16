#pragma once

enum SKY_GFX_HANDLE_TYPE
{
    SKY_GFX_HANDLE_TYPE_NONE,
    SKY_GFX_HANDLE_TYPE_PROGRAM,
    SKY_GFX_HANDLE_TYPE_TEXTURE
};

struct Sky_Gfx_Handle
{
    SKY_GFX_HANDLE_TYPE type;
    unsigned int handle;
};

void
sky_gfx_init();

void
sky_gfx_destroy();

void
sky_gfx_frame_start();

void
sky_gfx_frame_end();

Sky_Gfx_Handle
sky_gfx_program_new(const char *vshader, const char *fshader);

void
sky_gfx_program_free(Sky_Gfx_Handle program);

void
sky_gfx_program_use(Sky_Gfx_Handle program);

void
sky_gfx_program_set_bool(Sky_Gfx_Handle program, const char *name, bool value);

void
sky_gfx_program_set_int(Sky_Gfx_Handle program, const char *name, int value);

void
sky_gfx_program_set_float(Sky_Gfx_Handle program, const char *name, float value);

void
sky_gfx_program_set_vec2i(Sky_Gfx_Handle program, const char *name, int *value);

void
sky_gfx_program_set_vec3i(Sky_Gfx_Handle program, const char *name, int *value);

void
sky_gfx_program_set_vec4i(Sky_Gfx_Handle program, const char *name, int *value);

void
sky_gfx_program_set_vec2f(Sky_Gfx_Handle program, const char *name, float *value);

void
sky_gfx_program_set_vec3f(Sky_Gfx_Handle program, const char *name, float *value);

void
sky_gfx_program_set_vec4f(Sky_Gfx_Handle program, const char *name, float *value);

void
sky_gfx_program_set_mat4f(Sky_Gfx_Handle program, const char *name, float *value);

Sky_Gfx_Handle
sky_gfx_texture_load(const char *path);

void
sky_gfx_texture_free(Sky_Gfx_Handle texture);