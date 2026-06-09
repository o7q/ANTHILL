#include "renderers.hpp"

void Debug::Render::renderBoundingBox(Vec2i pos, const EntityCollider &collider, const Camera &camera,
                                      std::vector<RenderCommand> &commandsOut, Color color,
                                      unsigned int index)
{
    for (const Rectangle_i &rect : collider.getAll())
    {
        RectangleRenderCommandData data;
        data.a     = camera.cameraToViewport(rect.getA() + pos);
        data.b     = camera.cameraToViewport(rect.getB() + pos);
        data.color = color;
        commandsOut.push_back({index, data});
    }
}

void Debug::Render::renderAISightPoints(const AIPerception &perception, const Camera &camera,
                                        std::vector<RenderCommand> &commandsOut, Color color,
                                        unsigned int index)
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

void Debug::Render::renderAINavigation(const AINavigation &navigation, const Camera &camera,
                                       std::vector<RenderCommand> &commandsOut, Color color,
                                       unsigned int index)
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
