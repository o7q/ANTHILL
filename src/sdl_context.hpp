#pragma once

#include <SDL3/SDL_init.h>

class SDLContext
{
  public:
    SDLContext(SDL_InitFlags flags) { SDL_Init(flags); }
    ~SDLContext() { SDL_Quit(); }
};
