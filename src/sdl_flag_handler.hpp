#pragma once

#include <SDL3/SDL_init.h>

class SDLFlagHandler
{
  public:
    SDLFlagHandler(SDL_InitFlags flags) { SDL_Init(flags); }
    ~SDLFlagHandler() { SDL_Quit(); }
};
