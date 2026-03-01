#pragma once

#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "types/bounding_box.hpp"
#include "types/physics/verlet.hpp"
#include "world/world.hpp"

class Entity
{
  public:
    Entity(World &world) : r_world(world) {}
    virtual ~Entity() {}

    virtual void update(float dt) {}
    virtual void render(Viewport &viewport, const Camera &camera) {}

    VerletBody &getVerlet() { return m_verletBody; }

  protected:
    Vec2<int> calculateWorldPenetration_MTV(Vec2<int> pos);
    Vec2<float> calculateWorldPenetration_averageDirection(Vec2<int> pos);

  protected:
    World &r_world;
    VerletBody m_verletBody;
    BoundingBox m_collisionBox;
};
