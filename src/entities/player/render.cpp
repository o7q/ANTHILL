#include "backend/viewport/render_command.hpp"
#include "debug/renderers.hpp"
#include "entities/player/player_sprite.hpp"
#include "item/renderable.hpp"
#include "math/angle.hpp"
#include "player.hpp"
#include "sprite/sprite_animator.hpp"
#include <iostream>

void Player::render(const Camera &camera,
                    std::vector<RenderCommand> &commandsOut)
{
    // DEBUG_renderBoundingBox(m_body.getPosition(), m_boundingBox, camera,
    //                         commandsOut);

    const SpriteAnimator *head =
        m_sprite.getBodyPartAnimator(PlayerBodyPart::Head);
    const SpriteAnimator *torso =
        m_sprite.getBodyPartAnimator(PlayerBodyPart::Torso);
    const SpriteAnimator *legs =
        m_sprite.getBodyPartAnimator(PlayerBodyPart::Legs);

    if (head)
    {
        TextureRenderCommandData spriteData;
        spriteData.texture = head->getCurrentFrame();
        spriteData.position =
            camera.cameraToViewport(m_body.getPosition() + head->getOffset());
        spriteData.origin = head->getOrigin();
        spriteData.flipX = m_body.getPosition().x > m_aimPos.x;
        commandsOut.push_back({2, spriteData});
    }

    if (torso)
    {
        TextureRenderCommandData spriteData;
        spriteData.texture = torso->getCurrentFrame();
        spriteData.position =
            camera.cameraToViewport(m_body.getPosition() + torso->getOffset());
        spriteData.origin = torso->getOrigin();
        spriteData.flipX = m_body.getPosition().x > m_aimPos.x;
        commandsOut.push_back({2, spriteData});
    }

    if (legs)
    {
        TextureRenderCommandData spriteData;
        spriteData.texture = legs->getCurrentFrame();
        spriteData.position =
            camera.cameraToViewport(m_body.getPosition() + legs->getOffset());
        spriteData.origin = legs->getOrigin();
        spriteData.flipX = m_body.getPosition().x > m_aimPos.x;
        commandsOut.push_back({2, spriteData});
    }
}
