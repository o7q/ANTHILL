#include "entity_ai_perception_module.hpp"

void EntityAIPerceptionModule::renderDebug(Viewport &viewport,
                                           const Camera &camera)
{
    for (Vec2<int> p : m_sightPoints)
    {
        Vec2<int> ppos = camera.worldToViewport(p.x, p.y, viewport);
        viewport.setPixel(ppos.x, ppos.y, Color(255, 252, 99));
    }
}
