#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "game.hpp"
#include "logger/logger.hpp"

int main(int argc, char **argv)
{
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
    {
        Logger::log(Logger::LogLevel::Fatal, "Failing to initialize video!", true);
    }
    // SDL_InitSubSystem(SDL_INIT_AUDIO);
    // SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    // SDL_InitSubSystem(SDL_INIT_HAPTIC);
    // SDL_InitSubSystem(SDL_INIT_GAMEPAD);

    if (!TTF_Init())
    {
        Logger::log(Logger::LogLevel::Fatal, "Failing to initialize TTF!", true);
    }

    Game game;

    // why does this crash!!?!
    // TTF_Quit();

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    // SDL_QuitSubSystem(SDL_INIT_AUDIO);
    // SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
    // SDL_QuitSubSystem(SDL_INIT_HAPTIC);
    // SDL_QuitSubSystem(SDL_INIT_GAMEPAD);

    SDL_Quit();

    return 0;
}