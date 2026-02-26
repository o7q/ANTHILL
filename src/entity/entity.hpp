#pragma once

#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "math/bounding_box.hpp"
#include "math/verlet.hpp"
#include "world/world.hpp"

class Entity
{
  public:
    Entity() {}

    virtual void update() {}
    virtual void render(Viewport &viewport, const Camera &camera) {}

    VerletBody &getVerlet() { return m_verletBody; }

  protected:
    VerletBody m_verletBody;
    BoundingBox m_collisionBox;

    World *p_world = nullptr;
};
