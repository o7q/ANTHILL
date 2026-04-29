#include "backend/input/input_handler.hpp"
#include "game.hpp"
#include <SDL3/SDL_keycode.h>

void Game::init_binds()
{
    InputHandler &input = m_window.getInputHandler();

    input.addInput(InputID::Left, {{Input::ButtonType::Key, SDLK_A}});
    input.addInput(InputID::Right, {{Input::ButtonType::Key, SDLK_D}});
    input.addInput(InputID::Up, {{Input::ButtonType::Key, SDLK_W}});
    input.addInput(InputID::Down, {{Input::ButtonType::Key, SDLK_S}});
    input.addInput(InputID::Jump, {{Input::ButtonType::Key, SDLK_SPACE}});
    input.addInput(InputID::Reload, {{Input::ButtonType::Key, SDLK_R}});
    input.addInput(InputID::Shoot, {{Input::ButtonType::Mouse, SDL_BUTTON_LEFT}});
    input.addInput(InputID::Dash, {{Input::ButtonType::Key, SDLK_LSHIFT}});

    input.addInput(InputID::AltAction1, {{Input::ButtonType::Key, SDLK_1}});
    input.addInput(InputID::AltAction2, {{Input::ButtonType::Key, SDLK_2}});
    input.addInput(InputID::AltAction3, {{Input::ButtonType::Key, SDLK_3}});
    input.addInput(InputID::AltAction4, {{Input::ButtonType::Key, SDLK_4}});
    input.addInput(InputID::AltAction5, {{Input::ButtonType::Key, SDLK_5}});
    input.addInput(InputID::AltAction6, {{Input::ButtonType::Key, SDLK_6}});
    input.addInput(InputID::AltAction7, {{Input::ButtonType::Key, SDLK_7}});
    input.addInput(InputID::AltAction8, {{Input::ButtonType::Key, SDLK_8}});
    input.addInput(InputID::AltAction9, {{Input::ButtonType::Key, SDLK_9}});
    input.addInput(InputID::AltAction10, {{Input::ButtonType::Key, SDLK_0}});
}
