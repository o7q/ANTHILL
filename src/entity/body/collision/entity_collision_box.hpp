#pragma once

#include "entity_world_collision.hpp"
#include "types/bounding_box.hpp"
#include "world/world.hpp"

class EntityCollisionBox
{
  public:
    EntityCollisionBox(World &world) : m_worldHandler(world, m_boundingBox) {}

    EntityWorldCollisionHandler &getWorldHandler() { return m_worldHandler; }
    BoundingBox &getBoundingBox() { return m_boundingBox; }

  private:
    BoundingBox m_boundingBox;
    EntityWorldCollisionHandler m_worldHandler;
};
