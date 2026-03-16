#include "game.hpp"
#include "sdl_flag_handler.hpp"
#include <SDL3/SDL_init.h>

int main()
{
    SDLFlagHandler sdlFlagHandler(SDL_INIT_VIDEO);
    Game game(Vec2<unsigned int>(640, 480),
              Vec2<unsigned int>(320 * 2, 240 * 2));
    return 0;
}
