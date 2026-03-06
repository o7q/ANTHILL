#pragma once

#include "backend/event_handler.hpp"
#include "backend/types/vec.hpp"
#include "backend/window.hpp"
#include "scene/scene.hpp"
#include "scenes/testing/testing.hpp"
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
        init_binds();

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
    void init_binds();

  private:
    Window m_window;
    std::unique_ptr<Scene> currentScene = nullptr;
    SceneID m_currentSceneID = SceneID::Testing;
};
