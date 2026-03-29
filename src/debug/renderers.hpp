#pragma once

#include "backend/viewport/viewport.hpp"
#include "entity/modules/ai/navigation/ai_navigation.hpp"
#include "entity/modules/ai/perception/ai_perception.hpp"
#include "world/camera/camera.hpp"

inline void DEBUG_renderAINavigation(Viewport &viewport, const Camera &camera,
                                     const AINavigation &navigation)
{
    for (AINavigation::Checkpoint p : navigation.getCheckpoints())
    {
        Vec2i ppos = camera.worldToViewport(p.pos.x, p.pos.y, viewport);
        viewport.setPixel(ppos.x, ppos.y,
                          p.axis == AINavigation::Axis::Horizontal
                              ? Color(255, 105, 245)
                              : Color(255, 245, 105));
    }
}

inline void DEBUG_renderAINavigationInProgress(Viewport &viewport,
                                               const Camera &camera,
                                               AINavigation &navigation)
{
    for (Vec2i p : navigation.generatePath())
    {
        Vec2i ppos = camera.worldToViewport(p.x, p.y, viewport);
        viewport.setPixel(ppos.x, ppos.y, Color(255, 0, 0));
    }
}

inline void DEBUG_renderAIPerception(Viewport &viewport, const Camera &camera,
                                     const AIPerception &perception)
{
    for (Vec2i p : perception.getSightPoints())
    {
        Vec2i pos = camera.worldToViewport(p.x, p.y, viewport);
        viewport.setPixel(pos.x, pos.y, Color(255, 234, 77));
    }
}
