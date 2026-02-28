#pragma once

#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "math/bounding_box.hpp"
#include "math/verlet.hpp"
#include "world/world.hpp"
#include <optional>

class Entity
{
  public:
    Entity(World &world) : r_world(world) {}
    virtual ~Entity() {}

    virtual void update(float dt) {}
    virtual void render(Viewport &viewport, const Camera &camera) {}

    VerletBody &getVerlet() { return m_verletBody; }

  protected:
    Vec2<float> calculateWorldResolvePosition();

  private:
    std::optional<Vec2<float>>
    calculate_world_resolve_direction(Vec2<float> pos, Vec2<float> size);

  protected:
    World &r_world;
    VerletBody m_verletBody;
    BoundingBox m_collisionBox;
};
