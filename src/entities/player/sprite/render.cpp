#include "player_sprite.hpp"
#include "sprite/sprite_system.hpp"

void PlayerSprite::render(Vec2i pos, Vec2i aimPos, const Camera &camera,
                          std::vector<RenderCommand> &commandsOut)
{
    const SpriteAnimatorPositional *head  = m_head.getCurrentAnimator();
    const SpriteAnimatorPositional *torso = m_torso.getCurrentAnimator();
    const SpriteAnimatorPositional *legs  = m_legs.getCurrentAnimator();

    bool flipX = pos.x > aimPos.x;

    if (head)
    {
        TextureRenderCommandData spriteData;
        spriteData.texture  = head->getAnimator().getCurrentFrame();
        spriteData.position = camera.cameraToViewport(pos + head->getOffset());
        spriteData.origin   = head->getOrigin();
        spriteData.flipX    = flipX;
        commandsOut.push_back({4, spriteData});
    }

    if (torso)
    {
        TextureRenderCommandData spriteData;
        spriteData.texture  = torso->getAnimator().getCurrentFrame();
        spriteData.position = camera.cameraToViewport(pos + torso->getOffset());
        spriteData.origin   = torso->getOrigin();
        spriteData.flipX    = flipX;
        commandsOut.push_back({3, spriteData});
    }

    if (legs)
    {
        TextureRenderCommandData spriteData;
        spriteData.texture  = legs->getAnimator().getCurrentFrame();
        spriteData.position = camera.cameraToViewport(pos + legs->getOffset());
        spriteData.origin   = legs->getOrigin();
        spriteData.flipX    = flipX;
        commandsOut.push_back({2, spriteData});
    }
}
