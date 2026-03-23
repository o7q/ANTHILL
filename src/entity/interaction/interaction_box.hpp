#pragma once

#include "math/rectangle.hpp"
#include "world_interaction.hpp"

class InteractionBox
{
  public:
    InteractionBox() : m_worldHandler(m_boundingBox) {}

    WorldInteractionHandler &getWorldHandler() { return m_worldHandler; }
    StaticGridRectangle &getBoundingBox() { return m_boundingBox; }

    bool pointInside(Vec2i interactionBoxPos, Vec2i checkPos) const
    {
        return m_boundingBox.pointInside(checkPos.x - interactionBoxPos.x,
                                         checkPos.y - interactionBoxPos.y);
    }

  private:
    StaticGridRectangle m_boundingBox;
    WorldInteractionHandler m_worldHandler;
};
