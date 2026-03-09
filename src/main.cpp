#include "game.hpp"
#include "sdl_context.hpp"
#include <SDL3/SDL_init.h>

int main()
{
    SDLContext sdlContext(SDL_INIT_VIDEO);
    Game game(Vec2<unsigned int>(640, 480), Vec2<unsigned int>(480, 360));
    return 0;
}
