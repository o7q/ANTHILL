#pragma once

#include "entity_world_interaction.hpp"
#include "utils/bounding_box.hpp"

class EntityInteractionBox
{
  public:
    EntityInteractionBox(ParticleHandler &particles)
        : m_worldHandler(particles, m_boundingBox)
    {
    }

    EntityWorldInteractionHandler &getWorldHandler() { return m_worldHandler; }
    BoundingBox &getBoundingBox() { return m_boundingBox; }

    bool pointInside(Vec2<int> pos, int x, int y) const
    {
        return m_boundingBox.pointInside(x - pos.x, y - pos.y);
    }

  private:
    BoundingBox m_boundingBox;
    EntityWorldInteractionHandler m_worldHandler;
};
