#include "game.hpp"
#include <SDL3/SDL_keycode.h>

void Game::init_binds()
{
    m_window.getInputHandler().addInput(InputID::Left,
                                        {{Input::ButtonType::Key, SDLK_A}});
    m_window.getInputHandler().addInput(InputID::Right,
                                        {{Input::ButtonType::Key, SDLK_D}});
    m_window.getInputHandler().addInput(InputID::Up,
                                        {{Input::ButtonType::Key, SDLK_W}});
    m_window.getInputHandler().addInput(InputID::Down,
                                        {{Input::ButtonType::Key, SDLK_S}});

    m_window.getInputHandler().addInput(InputID::Jump,
                                        {{Input::ButtonType::Key, SDLK_SPACE}});

    m_window.getInputHandler().addInput(
        InputID::Action1, {{Input::ButtonType::Mouse, SDL_BUTTON_LEFT}});
    m_window.getInputHandler().addInput(
        InputID::Action2, {{Input::ButtonType::Mouse, SDL_BUTTON_RIGHT}});
    m_window.getInputHandler().addInput(InputID::AltAction1,
                                        {{Input::ButtonType::Key, SDLK_1}});
    m_window.getInputHandler().addInput(InputID::AltAction2,
                                        {{Input::ButtonType::Key, SDLK_2}});
    m_window.getInputHandler().addInput(InputID::AltAction3,
                                        {{Input::ButtonType::Key, SDLK_3}});
    m_window.getInputHandler().addInput(InputID::AltAction4,
                                        {{Input::ButtonType::Key, SDLK_4}});
    m_window.getInputHandler().addInput(InputID::AltAction5,
                                        {{Input::ButtonType::Key, SDLK_5}});
    m_window.getInputHandler().addInput(InputID::AltAction6,
                                        {{Input::ButtonType::Key, SDLK_6}});
    m_window.getInputHandler().addInput(InputID::AltAction7,
                                        {{Input::ButtonType::Key, SDLK_7}});
    m_window.getInputHandler().addInput(InputID::AltAction8,
                                        {{Input::ButtonType::Key, SDLK_8}});
    m_window.getInputHandler().addInput(InputID::AltAction9,
                                        {{Input::ButtonType::Key, SDLK_9}});
    m_window.getInputHandler().addInput(InputID::AltAction10,
                                        {{Input::ButtonType::Key, SDLK_0}});
}
