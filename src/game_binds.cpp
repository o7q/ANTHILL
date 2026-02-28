#include "game.hpp"

void Game::init_binds()
{
    m_window.getInputHandler().addInput("left",
                                        {{Input::ButtonType::Key, SDLK_A}});
    m_window.getInputHandler().addInput("right",
                                        {{Input::ButtonType::Key, SDLK_D}});
    m_window.getInputHandler().addInput("up",
                                        {{Input::ButtonType::Key, SDLK_W}});
    m_window.getInputHandler().addInput("down",
                                        {{Input::ButtonType::Key, SDLK_S}});

    m_window.getInputHandler().addInput(
        "action1", {{Input::ButtonType::Mouse, SDL_BUTTON_LEFT}});
    m_window.getInputHandler().addInput(
        "action2", {{Input::ButtonType::Mouse, SDL_BUTTON_RIGHT}});
    m_window.getInputHandler().addInput("secondaryAction1",
                                        {{Input::ButtonType::Key, SDLK_1}});
    m_window.getInputHandler().addInput("secondaryAction2",
                                        {{Input::ButtonType::Key, SDLK_2}});
    m_window.getInputHandler().addInput("secondaryAction3",
                                        {{Input::ButtonType::Key, SDLK_3}});
    m_window.getInputHandler().addInput("secondaryAction4",
                                        {{Input::ButtonType::Key, SDLK_4}});
    m_window.getInputHandler().addInput("secondaryAction5",
                                        {{Input::ButtonType::Key, SDLK_5}});

    m_window.getInputHandler().addInput("debug1",
                                        {{Input::ButtonType::Key, SDLK_COMMA}});
    m_window.getInputHandler().addInput(
        "debug2", {{Input::ButtonType::Key, SDLK_PERIOD}});

    m_window.getInputHandler().addInput("debugLeft",
                                        {{Input::ButtonType::Key, SDLK_LEFT}});
    m_window.getInputHandler().addInput("debugRight",
                                        {{Input::ButtonType::Key, SDLK_RIGHT}});
    m_window.getInputHandler().addInput("debugUp",
                                        {{Input::ButtonType::Key, SDLK_UP}});
    m_window.getInputHandler().addInput("debugDown",
                                        {{Input::ButtonType::Key, SDLK_DOWN}});
}
