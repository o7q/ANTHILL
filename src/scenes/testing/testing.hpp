#pragma once

#include "assets/assets.hpp"
#include "scene/scene.hpp"
#include "world/world.hpp"

class TestScene : public Scene
{
  public:
    TestScene(const Assets &assets, Window &window)
        : Scene(assets, window), m_world(m_backendEvents)
    {
    }

  protected:
    void onStart() override;
    void onTick() override;

  private:
    World m_world;
    Camera m_camera;
    Texture fpsText;
};
