#pragma once

#include "engine/backend/viewport.hpp"
#include "engine/camera.hpp"
#include "engine/entity/bounding_box.hpp"
#include "engine/math/verlet.hpp"
#include "engine/world/world.hpp"

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
