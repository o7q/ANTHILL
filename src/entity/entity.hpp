#pragma once

#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "entity/kinematic_controller.hpp"
#include "entity/world_collision_handler.hpp"
#include "world/world.hpp"

class Entity
{
  public:
    Entity(World &world) : r_world(world), m_worldCollisionHandler(world) {}
    virtual ~Entity() {}

    virtual void update(float dt) {}
    virtual void render(Viewport &viewport, const Camera &camera) {}

    KinematicController &getController() { return m_kinematicController; }

  protected:
    void handleMotion();

    void handleWorldInteractions(float dt);
    void handleWorldInteractions_colliding(float dt);
    void handleWorldInteractions_notColliding(float dt);

  protected:
    World &r_world;

    KinematicController m_kinematicController;
    WorldCollisionHandler m_worldCollisionHandler;
};
