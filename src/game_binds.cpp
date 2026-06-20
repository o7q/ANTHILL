#include "game.hpp"

#include "px/input/input_handler.hpp"
#include <SDL3/SDL_keycode.h>

void Game::init_binds()
{
    px::InputHandler &input = m_instance.input();

    input.createInput("left", {{px::Input::ButtonType::Key, SDLK_A}});
    input.createInput("right", {{px::Input::ButtonType::Key, SDLK_D}});
    input.createInput("up", {{px::Input::ButtonType::Key, SDLK_W}});
    input.createInput("down", {{px::Input::ButtonType::Key, SDLK_S}});
    input.createInput("jump", {{px::Input::ButtonType::Key, SDLK_SPACE}});
    input.createInput("shoot", {{px::Input::ButtonType::Mouse, SDL_BUTTON_LEFT}});
    input.createInput("dash", {{px::Input::ButtonType::Key, SDLK_LSHIFT}});
}
