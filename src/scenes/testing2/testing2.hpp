#pragma once

#include "assets/assets.hpp"
#include "scene/scene.hpp"

class TestScene2 : public Scene
{
  public:
    TestScene2(const Assets &assets, Window &window) : Scene(assets, window) {}

  protected:
    void onStart() override;
    void onTick() override;

    std::vector<Color> m_colors;
};
