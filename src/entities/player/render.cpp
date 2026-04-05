#include "backend/viewport/render_command.hpp"
#include "math/angle.hpp"
#include "player.hpp"
#include <iostream>

void Player::render(const Camera &camera,
                    std::vector<RenderCommand> &commandsOut)
{
    renderBox(camera, commandsOut);

    const Item *current = m_inventory.getSelectedItem();

    if (const IRenderable *renderable =
            dynamic_cast<const IRenderable *>(current))
    {
        TextureRenderCommandData gunData;
        gunData.texture = renderable->getTexture();
        gunData.position = camera.cameraToViewport(m_body.getPosition());
        gunData.origin = {9, 7};

        if (std::abs(m_angle) > 90.0f)
        {
            gunData.flipY = true;
        }

        gunData.rotateSettings = {Degrees(m_angle).radians(), 0};
        commandsOut.push_back({2, gunData});
    }
}

void Player::renderBox(const Camera &camera,
                       std::vector<RenderCommand> &commandsOut)
{
    RectangleRenderCommandData data;
    data.a =
        camera.cameraToViewport(m_boundingBox.getA() + m_body.getPosition());
    data.b =
        camera.cameraToViewport(m_boundingBox.getB() + m_body.getPosition());
    data.color = Color(255, 0, 0);

    commandsOut.push_back({1, data});
}
