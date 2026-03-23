#pragma once

#include "assets.hpp"
#include "backend/font/font.hpp"
#include "scene/scene.hpp"
#include "world/world.hpp"

class TestScene : public Scene
{
  public:
    TestScene(Window &window, const Assets &assets) : Scene(window, assets) {}

  protected:
    void onStart() override;
    void onTick() override;

  private:
    World m_world;

    float fps = 0;
    int fpsC = 0;
};
