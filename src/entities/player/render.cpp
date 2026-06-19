#include "debug/renderers.hpp"
#include "player.hpp"

#include "px/viewport/render_command.hpp"

void Player::render(const Camera &camera, std::vector<RenderCommand> &commandsOut)
{
    Debug::Render::renderBoundingBox(m_body.getPosition(), m_collider, camera, commandsOut);
}
