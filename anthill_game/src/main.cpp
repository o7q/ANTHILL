#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "game.hpp"
#include "engine/logger/logger.hpp"

bool sdl_init()
{
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
    {
        Log::log(Log::Level::Fatal, "Init", "Failing to initialize video!", true);
        return false;
    }

    if (!SDL_InitSubSystem(SDL_INIT_GAMEPAD))
    {
        Log::log(Log::Level::Fatal, "Init", "Failing to initialize gamepad!", true);
        return false;
    }

    if (!SDL_InitSubSystem(SDL_INIT_JOYSTICK))
    {
        Log::log(Log::Level::Fatal, "Init", "Failing to initialize joystick!", true);
        return false;
    }

    if (!TTF_Init())
    {
        Log::log(Log::Level::Fatal, "Init", "Failing to initialize TTF!", true);
        return false;
    }

    return true;
}

void sdl_quit()
{
    TTF_Quit();

    SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
    SDL_QuitSubSystem(SDL_INIT_GAMEPAD);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);

    SDL_Quit();
}

int main(int argc, char **argv)
{
    if (!sdl_init())
    {
        return 1;
    }

    // we must de-allocate game before sdl_quit() is called
    {
        Game game;
    }

    sdl_quit();

    return 0;
}