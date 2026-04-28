#include "backend/viewport/render_command.hpp"
#include "player.hpp"

void Player::render(const Camera &camera,
                    std::vector<RenderCommand> &commandsOut)
{
    // DEBUG_renderBoundingBox(m_body.getPosition(), m_boundingBox, camera,
    //                         commandsOut);

    m_sprite.render(m_body.getPosition(), m_aimPos, camera, commandsOut);
}
