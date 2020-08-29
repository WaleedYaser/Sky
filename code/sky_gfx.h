#pragma once

enum SKY_GFX_HANDLE_TYPE
{
    SKY_GFX_HANDLE_TYPE_NONE,
    SKY_GFX_HANDLE_TYPE_PROGRAM,
};

struct Sky_Gfx_Handle
{
    SKY_GFX_HANDLE_TYPE type;
    unsigned int handle;
};

Sky_Gfx_Handle
sky_gfx_program_new(const char *vshader, const char *fshader);

void
sky_gfx_program_free(Sky_Gfx_Handle program);

void
sky_gfx_program_use(Sky_Gfx_Handle program);