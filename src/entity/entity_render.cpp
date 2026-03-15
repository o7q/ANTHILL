#include "entity.hpp"
#include "utils/render.hpp"

void Entity::renderDebug_boundingBox(Viewport &viewport, const Camera &camera,
                                     Color color)
{
    Vec2<int> pos = m_body.getPosition().toGrid();

    Vec2<int> a = m_interactionBox.getBoundingBox().getA() + pos;
    Vec2<int> b = m_interactionBox.getBoundingBox().getB() + pos;

    a = camera.worldToViewport(a.x, a.y, viewport);
    b = camera.worldToViewport(b.x, b.y, viewport);

    Utils::Render::drawRectOutline(viewport, a, b, color);
}
