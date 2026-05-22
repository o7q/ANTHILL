#include "player.hpp"

#include "core/math/geometry/rectangle.hpp"
#include "core/viewport/render_command.hpp"

void Player::render(const Camera &camera, std::vector<RenderCommand> &commandsOut)
{
    if (m_dashTarget.has_value())
    {
        GridRectangle dashTarget = m_dashTarget.value();

        RectangleRenderCommandData rectRenderData;
        rectRenderData.a     = camera.cameraToViewport(dashTarget.getA());
        rectRenderData.b     = camera.cameraToViewport(dashTarget.getB());
        rectRenderData.color = Color(255, 0, 0);
        rectRenderData.fill  = false;

        commandsOut.push_back({10, rectRenderData});
    }

    m_sprite.render(m_body.getPosition(), m_aimPos, camera, commandsOut);
}
