#include "game.hpp"
#include <SDL3/SDL_init.h>

class SDLFlagHandler
{
  public:
    SDLFlagHandler(SDL_InitFlags flags) { SDL_InitSubSystem(flags); }
    ~SDLFlagHandler() { SDL_Quit(); }
};

int main()
{
    SDLFlagHandler flagHandler(SDL_INIT_VIDEO);

    Vec2u windowSize = {1280, 720};
    Vec2u aspect     = {4, 3};
    unsigned int scale = 70;
    // unsigned int scale = 150;
    Vec2u renderSize   = aspect * scale;
    Game game(windowSize, renderSize);

    return 0;
}
