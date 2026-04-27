#include "backend/viewport/render_command.hpp"
#include "player.hpp"
#include "sprite/sprite_animator.hpp"

void Player::render(const Camera &camera,
                    std::vector<RenderCommand> &commandsOut)
{
    // DEBUG_renderBoundingBox(m_body.getPosition(), m_boundingBox, camera,
    //                         commandsOut);

    const SpriteAnimator *head = m_sprite.getHead().getCurrentAnimator();
    const SpriteAnimator *torso = m_sprite.getTorso().getCurrentAnimator();
    const SpriteAnimator *legs = m_sprite.getLegs().getCurrentAnimator();

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
        commandsOut.push_back({3, spriteData});
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
