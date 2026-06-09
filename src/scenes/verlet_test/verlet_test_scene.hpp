#pragma once

#include "core/math/verlet/verlet.hpp"
#include "core/math/verlet/verlet_link.hpp"
#include "scene/scene.hpp"
#include <vector>

class VerletTestScene : public Scene
{
  public:
    VerletTestScene(Window &window) : Scene(window) { m_drawTex = Texture(r_window.getViewport().getSize()); }

  protected:
    void onStart() override;
    void onTick() override;

  private:
    std::vector<VerletBody> m_bodies;
    std::vector<VerletLink> m_links;

    Texture m_drawTex;
};
