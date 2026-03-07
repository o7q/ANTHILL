#pragma once

#include "collision/entity_collision_box.hpp"
#include "movement/entity_movement_controller.hpp"

class EntityBody
{
  public:
    EntityBody(World &world) : m_collisionBox(world) {}

    EntityMovementController &getMovementController()
    {
        return m_movementController;
    }
    EntityCollisionBox &getCollisionBox() { return m_collisionBox; }

  private:
    EntityMovementController m_movementController;
    EntityCollisionBox m_collisionBox;
};
