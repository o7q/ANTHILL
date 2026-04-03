#pragma once

#include "ai/navigation/ai_navigation.hpp"
#include "ai/perception/ai_perception.hpp"
#include "backend/viewport/viewport.hpp"
#include "math/rectangle.hpp"
#include "world/camera/camera.hpp"

inline void DEBUG_renderAINavigation(Viewport &viewport, const Camera &camera,
                                     const AINavigation &navigation)
{
    for (AINavigation::Checkpoint p : navigation.getCheckpoints())
    {
        Vec2i ppos = camera.worldToViewport(p.pos, viewport);
        viewport.setPixel(ppos.toUnsignedInt(),
                          p.axis == AINavigation::Axis::Horizontal
                              ? Color(255, 105, 245)
                              : Color(255, 245, 105));
    }
}

inline void DEBUG_renderBoundingBox(Viewport &viewport, const Camera &camera,
                                    Vec2i pos,
                                    const StaticGridRectangle &boundingBox,
                                    Color color = Color(43, 255, 223))
{
    Vec2i a = boundingBox.getA() + pos;
    Vec2i b = boundingBox.getB() + pos;

    a = camera.worldToViewport(a, viewport);
    b = camera.worldToViewport(b, viewport);

    viewport.drawRectOutline(a, b, color);
}

inline void DEBUG_renderAINavigationInProgress(Viewport &viewport,
                                               const Camera &camera,
                                               AINavigation &navigation,
                                               Vec2u navMeshRes)
{
    for (Vec2i p : navigation.generatePath())
    {
        viewport.setPixel(
            camera.worldToViewport(p * navMeshRes.toInt(), viewport)
                .toUnsignedInt(),
            Color(255, 0, 0));
    }
}

inline void DEBUG_renderAIPerception(Viewport &viewport, const Camera &camera,
                                     const AIPerception &perception)
{
    for (Vec2i p : perception.getSightPoints())
    {
        viewport.setPixel(camera.worldToViewport(p, viewport).toUnsignedInt(),
                          Color(255, 234, 77));
    }
}
