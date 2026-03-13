#include "entity_ai_module.hpp"

void AIModule::renderDebug(Viewport &viewport, const Camera &camera,
                           Vec2<int> headPos, float headAngle)
{
    for (Vec2<int> p : m_sightPoints)
    {
        Vec2<int> ppos = camera.worldToViewport(p.x, p.y, viewport);
        viewport.setPixel(ppos.x, ppos.y, Color(255, 252, 99));
    }

    for (Vec2<int> p : m_pathCheckpoints)
    {
        Vec2<int> ppos = camera.worldToViewport(p.x, p.y, viewport);
        viewport.setPixel(ppos.x, ppos.y, Color(255, 105, 245));
    }
}
