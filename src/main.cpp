#include <SDL3/SDL.h>

#include "game.hpp"

int main(int argc, char **argv)
{
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    SDL_InitSubSystem(SDL_INIT_AUDIO);
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    SDL_InitSubSystem(SDL_INIT_HAPTIC);
    SDL_InitSubSystem(SDL_INIT_GAMEPAD);

    Game game;

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
    SDL_QuitSubSystem(SDL_INIT_HAPTIC);
    SDL_QuitSubSystem(SDL_INIT_GAMEPAD);

    SDL_Quit();

    return 0;
}