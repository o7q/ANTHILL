#include "entity.hpp"

void Entity::renderDebug_boundingBox(Viewport &viewport, const Camera &camera,
                                     Color color)
{
    Vec2i pos = m_body.getPosition().toGrid();

    Vec2i a = m_interactionBox.getBoundingBox().getA() + pos;
    Vec2i b = m_interactionBox.getBoundingBox().getB() + pos;

    a = camera.worldToViewport(a.x, a.y, viewport);
    b = camera.worldToViewport(b.x, b.y, viewport);

    viewport.drawRectOutline(a, b, color);
}
