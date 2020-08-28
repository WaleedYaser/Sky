#pragma once

#define SKY_GAME_API __declspec(dllexport)
#define SKY_GAME_API_PROC_NAME "sky_game_api"

#ifdef __cplusplus
extern "C" {
#endif

enum SKY_KEY
{
    SKY_KEY_MOUSE_LEFT,
    SKY_KEY_MOUSE_MIDDLE,
    SKY_KEY_MOUSE_RIGHT,

    SKY_KEY_LEFT,
    SKY_KEY_RIGHT,
    SKY_KEY_UP,
    SKY_KEY_DOWN,
    SKY_KEY_SPACE,
    SKY_KEY_COUNT
};

typedef struct Sky_Key_State
{
    bool pressed;
    bool released;
    bool down;

    int pressed_count;
    int released_count;
} Sky_Key_State;

typedef struct Sky_Input
{
    int mouse_x, mouse_y;
    int mouse_dx, mouse_dy;
    int mouse_wheel;
    Sky_Key_State keys[SKY_KEY_COUNT];
} Sky_Input;

typedef struct Sky_Game
{
    bool quit;
    int width, height;
    Sky_Input input;
} Sky_Game;

typedef struct Sky_Game_Api
{
    void (*construct)(Sky_Game *self);
    void (*destruct)(Sky_Game *self);

    void (*reload)(Sky_Game *self);
    void (*loop)(Sky_Game *self);
} Sky_Game_Api;

SKY_GAME_API Sky_Game_Api *
sky_game_api();

typedef Sky_Game_Api * (*sky_game_api_proc)(void);

#ifdef __cplusplus
}
#endif