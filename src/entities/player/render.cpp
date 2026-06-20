#include "player.hpp"

#include "debug/renderers.hpp"
#include "px/window/render_command.hpp"

void Player::render(const Camera &camera, std::vector<px::RenderCommand> &commandsOut)
{
    Debug::Render::renderBoundingBox(m_body.getPosition(), m_collider, camera, commandsOut);
}
