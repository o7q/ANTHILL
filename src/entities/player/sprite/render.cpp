#include "player_sprite.hpp"

void PlayerSprite::render(Vec2i pos, Vec2i aimPos, const Camera &camera,
                          std::vector<RenderCommand> &commandsOut)
{
    const SpriteAnimator *head = m_head.getCurrentAnimator();
    const SpriteAnimator *torso = m_torso.getCurrentAnimator();
    const SpriteAnimator *legs = m_legs.getCurrentAnimator();

    bool flipX = pos.x > aimPos.x;

    if (head)
    {
        TextureRenderCommandData spriteData;
        spriteData.texture = head->getCurrentFrame();
        spriteData.position = camera.cameraToViewport(pos + head->getOffset());
        spriteData.origin = head->getOrigin();
        spriteData.flipX = flipX;
        commandsOut.push_back({2, spriteData});
    }

    if (torso)
    {
        TextureRenderCommandData spriteData;
        spriteData.texture = torso->getCurrentFrame();
        spriteData.position = camera.cameraToViewport(pos + torso->getOffset());
        spriteData.origin = torso->getOrigin();
        spriteData.flipX = flipX;
        commandsOut.push_back({3, spriteData});
    }

    if (legs)
    {
        TextureRenderCommandData spriteData;
        spriteData.texture = legs->getCurrentFrame();
        spriteData.position = camera.cameraToViewport(pos + legs->getOffset());
        spriteData.origin = legs->getOrigin();
        spriteData.flipX = flipX;
        commandsOut.push_back({2, spriteData});
    }
}
