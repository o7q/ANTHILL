#pragma once

#include "engine/backend/event_handler.hpp"
#include "engine/backend/types/vec.hpp"
#include "engine/backend/window.hpp"
#include "engine/scene.hpp"
#include "scenes/testing.hpp"
#include <SDL3/SDL_keycode.h>
#include <memory>

class Game
{
  public:
    Game(Vec2<unsigned int> windowSize, Vec2<unsigned int> viewportSize)
        : m_window(windowSize, viewportSize)
    {
        start();
    }
    Game(const Game &other) = delete;
    Game &operator=(const Game &other) = delete;

  private:
    void start()
    {
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

        m_window.getInputHandler().addInput(
            "debug1", {{Input::ButtonType::Key, SDLK_COMMA}});
        m_window.getInputHandler().addInput(
            "debug2", {{Input::ButtonType::Key, SDLK_PERIOD}});

        m_window.getInputHandler().addInput(
            "debugLeft", {{Input::ButtonType::Key, SDLK_LEFT}});
        m_window.getInputHandler().addInput(
            "debugRight", {{Input::ButtonType::Key, SDLK_RIGHT}});
        m_window.getInputHandler().addInput(
            "debugUp", {{Input::ButtonType::Key, SDLK_UP}});
        m_window.getInputHandler().addInput(
            "debugDown", {{Input::ButtonType::Key, SDLK_DOWN}});

        m_window.getTimeHandler().setTargetFramerate(144);

        currentScene = std::make_unique<TestScene>(m_window);

        while (!m_window.getEventHandler().didEventOccur(
            EventHandler::EventType::WINDOW_QUIT))
        {
            m_window.frameStart();
            m_window.getViewport().clear();

            update_loop();

            m_window.render();
            m_window.frameEnd();
        }
    }

  private:
    void update_loop();

  private:
    Window m_window;
    std::unique_ptr<Scene> currentScene = nullptr;
    SceneID m_currentSceneID = SceneID::Testing;
};
