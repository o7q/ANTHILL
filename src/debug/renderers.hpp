#pragma once

#include "ai/navigation/ai_navigation.hpp"
#include "ai/perception/ai_perception.hpp"
#include "camera/camera.hpp"
#include "entity/collider/entity_collider.hpp"
#include "px/window/draw_types.hpp"
#include <vector>

namespace Debug
{
namespace Render
{
void renderBoundingBox(px::Vec2i pos, const EntityCollider &collider, const Camera &camera,
                       std::vector<px::DrawCommand> &commandsOut, px::Color color = px::Color(255, 0, 0),
                       unsigned int index = 1);

void renderAISightPoints(const AIPerception &perception, const Camera &camera,
                         std::vector<px::DrawCommand> &commandsOut, px::Color color = px::Color(255, 255, 0),
                         unsigned int index = 1);

void renderAINavigation(const AINavigation &navigation, const Camera &camera,
                        std::vector<px::DrawCommand> &commandsOut, px::Color color = px::Color(15, 255, 207),
                        unsigned int index = 1);
} // namespace Render
} // namespace Debug
