#pragma once

#include "assets/assets.hpp"
#include "backend/texture/texture.hpp"
#include "math/vec.hpp"
#include "scene/scene.hpp"

class TestScene2 : public Scene
{
  public:
    TestScene2(const Assets &assets, Window &window) : Scene(assets, window) {}

  protected:
    void onStart() override;
    void onTick() override;

  private:
    Texture m_screen =
        Texture({r_viewport.getSize().x, r_viewport.getSize().y});
};
