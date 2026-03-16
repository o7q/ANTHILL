#pragma once

#include "utils/bounding_box.hpp"
#include "world_interaction.hpp"

class InteractionBox
{
  public:
    InteractionBox() : m_worldHandler(m_boundingBox) {}

    WorldInteractionHandler &getWorldHandler() { return m_worldHandler; }
    BoundingBox &getBoundingBox() { return m_boundingBox; }

    bool pointInside(Vec2<int> pos, int x, int y) const
    {
        return m_boundingBox.pointInside(x - pos.x, y - pos.y);
    }

  private:
    BoundingBox m_boundingBox;
    WorldInteractionHandler m_worldHandler;
};
