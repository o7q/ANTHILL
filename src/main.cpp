#include "game.hpp"
#include "sdl_flag_handler.hpp"
#include <SDL3/SDL_init.h>

int main()
{
    SDLFlagHandler sdlFlagHandler(SDL_INIT_VIDEO);
    Game game({1280, 720}, {384, 216});
    return 0;
}
