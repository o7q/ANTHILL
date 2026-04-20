#include "backend/viewport/render_command.hpp"
#include "debug/renderers.hpp"
#include "math/angle.hpp"
#include "player.hpp"
#include "sprite/sprite_animator.hpp"
#include <iostream>

void Player::render(const Camera &camera,
                    std::vector<RenderCommand> &commandsOut)
{
    // DEBUG_renderBoundingBox(m_body.getPosition(), m_boundingBox, camera,
    //                         commandsOut);

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

    const SpriteAnimator *animator = m_sprite.getCurrentAnimator();

    if (animator)
    {
        TextureRenderCommandData spriteData;
        spriteData.texture = animator->getCurrentFrame();
        spriteData.position = camera.cameraToViewport(m_body.getPosition());
        spriteData.origin = animator->getOrigin();
        spriteData.flipX = m_body.getVelocity().x < 0;
        commandsOut.push_back({2, spriteData});
    }
}
