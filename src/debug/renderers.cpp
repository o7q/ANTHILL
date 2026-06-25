#include "renderers.hpp"
#include "px/window/draw_types.hpp"

void Debug::Render::renderBoundingBox(px::Vec2i pos, const EntityCollider &collider, const Camera &camera,
                                      std::vector<px::DrawCommand> &commandsOut, px::Color color,
                                      unsigned int index)
{
    for (const px::Rectangle_i &rect : collider.getAll())
    {
        px::RectangleDrawConfig config;
        config.rectangle = rect;
        config.rectangle.setPosition(camera.cameraToRenderer(pos + rect.getPosition()));
        config.color = color;
        commandsOut.push_back({index, config});
    }
}

void Debug::Render::renderAISightPoints(const AIPerception &perception, const Camera &camera,
                                        std::vector<px::DrawCommand> &commandsOut, px::Color color,
                                        unsigned int index)
{
    std::vector<px::Vec2i> points = perception.getSightPoints();

    for (px::Vec2i &p : points)
    {
        p = camera.cameraToRenderer(p);
    }

    px::PointsDrawConfig config;
    config.points = points;
    config.color  = color;

    commandsOut.push_back({index, config});
}

void Debug::Render::renderAINavigation(const AINavigation &navigation, const Camera &camera,
                                       std::vector<px::DrawCommand> &commandsOut, px::Color color,
                                       unsigned int index)
{
    std::vector<AINavigation::Checkpoint> checkpoints = navigation.getCheckpoints();
    std::vector<px::Vec2i> points;

    for (AINavigation::Checkpoint &checkpoint : checkpoints)
    {
        points.push_back(camera.cameraToRenderer(checkpoint.pos));
    }

    px::PointsDrawConfig config;
    config.points = points;
    config.color  = color;

    commandsOut.push_back({index, config});
}
