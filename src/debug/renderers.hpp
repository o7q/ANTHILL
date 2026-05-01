#pragma once

#include "ai/perception/ai_perception.hpp"
#include "backend/viewport/render_command.hpp"
#include "camera/camera.hpp"
#include "math/rectangle.hpp"
#include <vector>

inline void DEBUG_renderBoundingBox(Vec2i pos, const StaticGridRectangle &bb, const Camera &camera,
                                    std::vector<RenderCommand> &commandsOut, Color color = Color(255, 0, 0),
                                    unsigned int index = 1)
{
    RectangleRenderCommandData data;
    data.a     = camera.cameraToViewport(bb.getA() + pos);
    data.b     = camera.cameraToViewport(bb.getB() + pos);
    data.color = color;

    commandsOut.push_back({index, data});
}

inline void DEBUG_renderAISightPoints(const AIPerception &perception, const Camera &camera,
                                      std::vector<RenderCommand> &commandsOut,
                                      Color color = Color(255, 255, 0), unsigned int index = 1)
{
    std::vector<Vec2i> points = perception.getSightPoints();

    for (Vec2i &p : points)
    {
        p = camera.cameraToViewport(p);
    }

    PointsRenderCommandData data;
    data.points = points;
    data.color  = color;

    commandsOut.push_back({index, data});
}
