#pragma once

#include "px/verlet/verlet.hpp"
#include "px/verlet/verlet_link.hpp"
#include "scene/scene.hpp"
#include <vector>

class VerletTestScene : public Scene
{
  public:
    VerletTestScene(px::Instance &instance) : Scene(instance, {280, 210}) {}

  protected:
    void onStart() override;
    void onTick() override;

  private:
    std::vector<px::VerletBody> m_bodies;
    std::vector<px::VerletLink> m_links;
};
