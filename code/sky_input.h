#pragma once

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
    float delta_time;
    int mouse_x, mouse_y;
    int mouse_dx, mouse_dy;
    float mouse_wheel;
    Sky_Key_State keys[SKY_KEY_COUNT];
} Sky_Input;