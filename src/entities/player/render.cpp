#include "player.hpp"

#include "debug/renderers.hpp"
#include "px/canvas/draw_types.hpp"

void Player::render(const Camera &camera, std::vector<px::DrawCommand> &commandsOut)
{
    Debug::Render::renderBoundingBox(m_body.getPosition(), m_collider, camera, commandsOut);
}
