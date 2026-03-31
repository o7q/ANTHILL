#include "entity.hpp"

void Entity::DEBUG_renderBoundingBox(Viewport &viewport, const Camera &camera,
                                     Color color)
{
    Vec2i pos = m_body.getPosition().toGrid();

    Vec2i a = m_interactionBox.getBoundingBox().getA() + pos;
    Vec2i b = m_interactionBox.getBoundingBox().getB() + pos;

    a = camera.worldToViewport(a, viewport);
    b = camera.worldToViewport(b, viewport);

    viewport.drawRectOutline(a, b, color);
}
