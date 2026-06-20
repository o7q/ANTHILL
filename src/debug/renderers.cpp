#include "renderers.hpp"

void Debug::Render::renderBoundingBox(px::Vec2i pos, const EntityCollider &collider, const Camera &camera,
                                      std::vector<px::RenderCommand> &commandsOut, px::Color color,
                                      unsigned int index)
{
    for (const px::Rectangle_i &rect : collider.getAll())
    {
        px::RectangleRenderCommandData data;
        data.rectangle = rect;
        data.rectangle.setPosition(camera.cameraToRenderer(pos + rect.getPosition()));
        data.color = color;
        commandsOut.push_back({index, data});
    }
}

void Debug::Render::renderAISightPoints(const AIPerception &perception, const Camera &camera,
                                        std::vector<px::RenderCommand> &commandsOut, px::Color color,
                                        unsigned int index)
{
    std::vector<px::Vec2i> points = perception.getSightPoints();

    for (px::Vec2i &p : points)
    {
        p = camera.cameraToRenderer(p);
    }

    px::PointsRenderCommandData data;
    data.points = points;
    data.color  = color;

    commandsOut.push_back({index, data});
}

void Debug::Render::renderAINavigation(const AINavigation &navigation, const Camera &camera,
                                       std::vector<px::RenderCommand> &commandsOut, px::Color color,
                                       unsigned int index)
{
    std::vector<AINavigation::Checkpoint> checkpoints = navigation.getCheckpoints();
    std::vector<px::Vec2i> points;

    for (AINavigation::Checkpoint &checkpoint : checkpoints)
    {
        points.push_back(camera.cameraToRenderer(checkpoint.pos));
    }

    px::PointsRenderCommandData data;
    data.points = points;
    data.color  = color;

    commandsOut.push_back({index, data});
}
