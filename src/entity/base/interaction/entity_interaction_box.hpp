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

  private:
    BoundingBox m_boundingBox;
    EntityWorldInteractionHandler m_worldHandler;
};
