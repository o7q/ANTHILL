#pragma once

#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "collision/entity_collision_box.hpp"
#include "movement/entity_movement.hpp"
#include "world/world.hpp"

class Entity
{
  public:
    Entity(World &world) : r_world(world), m_collisionBox(world) {}
    virtual ~Entity() {}

    virtual void update(float dt) {}
    virtual void render(Viewport &viewport, const Camera &camera) {}

    EntityMovementController &getMovementController()
    {
        return m_movementController;
    }

  protected:
    void handleMotion();

    void handleWorldInteractions(float dt);
    void handleWorldInteractions_colliding(float dt);
    void handleWorldInteractions_notColliding(float dt);

  protected:
    World &r_world;

    EntityMovementController m_movementController;
    EntityCollisionBox m_collisionBox;
};
