#pragma once

#include "ai/navigation/ai_navigation.hpp"
#include "ai/perception/ai_perception.hpp"
#include "camera/camera.hpp"
#include "core/math/rectangle.hpp"
#include "core/viewport/render_command.hpp"
#include "entity/collider/entity_collider.hpp"
#include <vector>

inline void DEBUG_renderBoundingBox(Vec2i pos, const EntityCollider &collider, const Camera &camera,
                                    std::vector<RenderCommand> &commandsOut, Color color = Color(255, 0, 0),
                                    unsigned int index = 1)
{
    for (const GridRectangle &rect : collider.getAll())
    {
        RectangleRenderCommandData data;
        data.a     = camera.cameraToViewport(rect.getA() + pos);
        data.b     = camera.cameraToViewport(rect.getB() + pos);
        data.color = color;
        commandsOut.push_back({index, data});
    }
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

inline void DEBUG_renderAINavigation(const AINavigation &navigation, const Camera &camera,
                                     std::vector<RenderCommand> &commandsOut,
                                     Color color = Color(15, 255, 207), unsigned int index = 1)
{
    std::vector<AINavigation::Checkpoint> checkpoints = navigation.getCheckpoints();
    std::vector<Vec2i> points;

    for (AINavigation::Checkpoint &checkpoint : checkpoints)
    {
        points.push_back(camera.cameraToViewport(checkpoint.pos));
    }

    PointsRenderCommandData data;
    data.points = points;
    data.color  = color;

    commandsOut.push_back({index, data});
}
