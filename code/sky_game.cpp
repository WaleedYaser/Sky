#include "sky_game.h"

static void
_sky_game_construct(Sky_Game *self)
{
    *self = {};
}

static void
_sky_game_destruct(Sky_Game *self)
{

}

static void
_sky_game_loop(Sky_Game *self)
{
    self->count += 1;
}

Sky_Game_Api *
sky_game_api()
{
    static Sky_Game_Api api;

    api.construct = _sky_game_construct;
    api.destruct = _sky_game_destruct;
    api.loop = _sky_game_loop;

    return &api;
}

