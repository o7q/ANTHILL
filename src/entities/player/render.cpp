#include "math/rectangle.hpp"
#include "player.hpp"

#include "backend/viewport/render_command.hpp"

void Player::render(const Camera &camera, std::vector<RenderCommand> &commandsOut)
{
    for (PositionalGridRectangle &rect : m_highlightRects)
    {
        RectangleRenderCommandData rdata;
        rdata.a     = camera.cameraToViewport(rect.getA());
        rdata.b     = camera.cameraToViewport(rect.getB());
        rdata.color = Color(255, 0, 0);
        rdata.fill  = false;

        commandsOut.push_back({10, rdata});
    }

    m_sprite.render(m_body.getPosition(), m_aimPos, camera, commandsOut);
}
