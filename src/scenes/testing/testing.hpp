#pragma once

#include "assets/assets.hpp"
#include "backend/animated_texture/animated_texture.hpp"
#include "scene/scene.hpp"
#include "world/world.hpp"

class TestScene : public Scene
{
  public:
    TestScene(const Assets &assets, Window &window)
        : Scene(assets, window), m_world(m_backendEvents),
          m_animTex("assets/images/cat_boinga.png", {15, 25})
    {
    }

  protected:
    void onStart() override;
    void onTick() override;

  private:
    World m_world;
    AnimatedTexture m_animTex;
};
