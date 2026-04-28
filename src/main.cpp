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
    Game game({1920, 1080}, {480, 270});
    return 0;
}
