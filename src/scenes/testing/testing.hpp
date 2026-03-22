#pragma once

#include "assets.hpp"
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
};
