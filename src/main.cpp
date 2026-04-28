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
    Game game({1280, 720}, Vec2u(320, 180));
    return 0;
}
