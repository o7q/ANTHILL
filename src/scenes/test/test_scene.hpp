#pragma once

#include "math/physics/verlet.hpp"
#include "math/physics/verlet_link.hpp"
#include "scene/scene.hpp"
#include <vector>

class TestScene : public Scene
{
  public:
    TestScene(Window &window, const Assets &assets) : Scene(SceneID::Test, window, assets)
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
