#pragma once

#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "dynamic_body/entity_dynamic_body.hpp"
#include "world/world.hpp"
#include "world_collision/entity_world_collision_handler.hpp"

class Entity
{
  public:
    Entity(World &world) : r_world(world), m_worldCollisionHandler(world) {}
    virtual ~Entity() {}

    virtual void update(float dt) {}
    virtual void render(Viewport &viewport, const Camera &camera) {}

    EntityDynamicBody &getBody() { return m_body; }

  protected:
    void handleMotion();

    void handleWorldInteractions(float dt);
    void handleWorldInteractions_colliding(float dt);
    void handleWorldInteractions_notColliding(float dt);

  protected:
    World &r_world;

    EntityDynamicBody m_body;
    EntityWorldCollisionHandler m_worldCollisionHandler;
};
