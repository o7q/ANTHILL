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

    Vec2u size = {1280, 720};
    // Vec2u renderSize = {320, 180};
    Vec2u renderSize = {5 * 60, 4 * 60};
    Game game(size, renderSize);
    return 0;
}
