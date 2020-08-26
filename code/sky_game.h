#pragma once

#define SKY_GAME_API __declspec(dllexport)
#define SKY_GAME_API_PROC_NAME "sky_game_api"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Sky_Game
{
    int count;
    bool quit;
} Sky_Game;

typedef struct Sky_Game_Api
{
    void (*construct)(Sky_Game *self);
    void (*destruct)(Sky_Game *self);

    void (*loop)(Sky_Game *self);
} Sky_Game_Api;

SKY_GAME_API Sky_Game_Api *
sky_game_api();

typedef Sky_Game_Api * (*sky_game_api_proc)(void);

#ifdef __cplusplus
}
#endif