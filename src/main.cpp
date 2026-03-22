#include "game.hpp"
#include "sdl_flag_handler.hpp"
#include <SDL3/SDL_init.h>

int main()
{
    SDLFlagHandler sdlFlagHandler(SDL_INIT_VIDEO);
    Game game(Vec2u(640, 480), Vec2u(320, 240));
    return 0;
}
