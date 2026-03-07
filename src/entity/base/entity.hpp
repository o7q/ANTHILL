#pragma once

#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "collision/entity_collision_box.hpp"
#include "entity/base/kinetic_body/entity_kinetic_body.hpp"
#include "world/world.hpp"

class Entity
{
  public:
    Entity(World &world) : r_world(world), m_collisionBox(world) {}
    virtual ~Entity() {}

    virtual void update(float dt) {}
    virtual void render(Viewport &viewport, const Camera &camera) {}

    EntityKineticBody &getBody() { return m_body; }

  protected:
    void handleMotion();

    virtual void handleWorldInteraction(float dt);

  protected:
    World &r_world;

    EntityKineticBody m_body;
    EntityCollisionBox m_collisionBox;
};
