#pragma once

#include "math/verlet/verlet.hpp"
#include "math/verlet/verlet_link.hpp"
#include "scene/scene.hpp"
#include <vector>

class TestScene : public Scene
{
  public:
    TestScene(Window &window, const Assets &assets) : Scene(window, assets)
    {
        m_drawTex = Texture(r_window.getViewport().getSize());
    }

  protected:
    void onStart() override;
    void onTick() override;

  private:
    std::vector<VerletBody> m_bodies;
    std::vector<VerletLink> m_links;

    Texture m_drawTex;
};
