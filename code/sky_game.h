#pragma once

#include "sky_cam.h"
#include "sky_input.h"
#include "sky_terrain.h"

#define SKY_GAME_API __declspec(dllexport)
#define SKY_GAME_API_PROC_NAME "sky_game_api"

#define SKY_GAME_MAP_WIDTH 11
#define SKY_GAME_MAP_HEIGHT 11
#define SKY_GAME_MAX_VERTEX_BUFFER_SIZE (SKY_GAME_MAP_WIDTH * SKY_GAME_MAP_HEIGHT * 12 * 3 * 3 * sizeof(float))

typedef struct Sky_Game
{
    bool quit;
    int width, height;
    Sky_Input input;
    Sky_Cam cam;
    Sky_Terrain iseland_terrain;
    Sky_Terrain water_terrain;

    unsigned int skybox_VAO;
} Sky_Game;

typedef struct Sky_Game_Api
{
    void (*init)(Sky_Game *self);
    void (*destoy)(Sky_Game *self);

    void (*reload)(Sky_Game *self);
    void (*loop)(Sky_Game *self);
} Sky_Game_Api;

#ifdef __cplusplus
extern "C" {
#endif

SKY_GAME_API Sky_Game_Api *
sky_game_api();

#ifdef __cplusplus
}
#endif

typedef Sky_Game_Api * (*sky_game_api_proc)(void);