#include "player.hpp"

#include "backend/viewport/render_command.hpp"

void Player::render(const Camera &camera, std::vector<RenderCommand> &commandsOut)
{
    m_sprite.render(m_body.getPosition(), m_aimPos, camera, commandsOut);
}
