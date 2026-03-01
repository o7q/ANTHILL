#pragma once

#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "entity/collision_handler.hpp"
#include "entity/kinematic_controller.hpp"
#include "world/world.hpp"

class Entity
{
  public:
    Entity(World &world) : r_world(world) {}
    virtual ~Entity() {}

    virtual void update(float dt) {}
    virtual void render(Viewport &viewport, const Camera &camera) {}

    KinematicController &getController() { return m_kinematicController; }

  protected:
    World &r_world;

    KinematicController m_kinematicController;
    CollisionHandler m_collisionHandler;
};
