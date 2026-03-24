#include "game.hpp"
#include "sdl_flag_handler.hpp"
#include <SDL3/SDL_init.h>

int main()
{
    SDLFlagHandler sdlFlagHandler(SDL_INIT_VIDEO);
    Game game(Vec2u(1280, 720), Vec2u(480, 270));
    return 0;
}
