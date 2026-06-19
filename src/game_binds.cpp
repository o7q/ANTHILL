#include "game.hpp"

#include "px/input/input_handler.hpp"
#include <SDL3/SDL_keycode.h>

void Game::init_binds()
{
    InputHandler &input = m_window.getInput();

    input.assignInput(InputID::Left, {{Input::ButtonType::Key, SDLK_A}});
    input.assignInput(InputID::Right, {{Input::ButtonType::Key, SDLK_D}});
    input.assignInput(InputID::Up, {{Input::ButtonType::Key, SDLK_W}});
    input.assignInput(InputID::Down, {{Input::ButtonType::Key, SDLK_S}});
    input.assignInput(InputID::Jump, {{Input::ButtonType::Key, SDLK_SPACE}});
    input.assignInput(InputID::Slam, {{Input::ButtonType::Key, SDLK_LCTRL}});
    input.assignInput(InputID::Shoot, {{Input::ButtonType::Mouse, SDL_BUTTON_LEFT}});
    input.assignInput(InputID::Dash, {{Input::ButtonType::Key, SDLK_LSHIFT}});

    input.assignInput(InputID::AltAction1, {{Input::ButtonType::Key, SDLK_1}});
    input.assignInput(InputID::AltAction2, {{Input::ButtonType::Key, SDLK_2}});
    input.assignInput(InputID::AltAction3, {{Input::ButtonType::Key, SDLK_3}});
    input.assignInput(InputID::AltAction4, {{Input::ButtonType::Key, SDLK_4}});
    input.assignInput(InputID::AltAction5, {{Input::ButtonType::Key, SDLK_5}});
    input.assignInput(InputID::AltAction6, {{Input::ButtonType::Key, SDLK_6}});
    input.assignInput(InputID::AltAction7, {{Input::ButtonType::Key, SDLK_7}});
    input.assignInput(InputID::AltAction8, {{Input::ButtonType::Key, SDLK_8}});
    input.assignInput(InputID::AltAction9, {{Input::ButtonType::Key, SDLK_9}});
    input.assignInput(InputID::AltAction10, {{Input::ButtonType::Key, SDLK_0}});
}
