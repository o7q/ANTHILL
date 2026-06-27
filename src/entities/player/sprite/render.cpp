#include "player_sprite.hpp"
#include "px/canvas/draw_types.hpp"
#include "sprite/sprite_system.hpp"

void PlayerSprite::render(px::Vec2i pos, px::Vec2i aimPos, const Camera &camera,
                          std::vector<px::DrawCommand> &commandsOut)
{
    const SpriteAnimatorPositional *head  = m_head.getCurrentAnimator();
    const SpriteAnimatorPositional *torso = m_torso.getCurrentAnimator();
    const SpriteAnimatorPositional *legs  = m_legs.getCurrentAnimator();

    bool flipX = pos.x > aimPos.x;

    if (head)
    {
        px::TextureDrawConfig spriteData;
        spriteData.texture  = head->getAnimator().getCurrentFrame();
        spriteData.position = camera.cameraToRenderer(pos + head->getOffset());
        spriteData.origin   = head->getOrigin();
        spriteData.flipX    = flipX;
        commandsOut.push_back({4, spriteData});
    }

    if (torso)
    {
        px::TextureDrawConfig spriteData;
        spriteData.texture  = torso->getAnimator().getCurrentFrame();
        spriteData.position = camera.cameraToRenderer(pos + torso->getOffset());
        spriteData.origin   = torso->getOrigin();
        spriteData.flipX    = flipX;
        commandsOut.push_back({3, spriteData});
    }

    if (legs)
    {
        px::TextureDrawConfig spriteData;
        spriteData.texture  = legs->getAnimator().getCurrentFrame();
        spriteData.position = camera.cameraToRenderer(pos + legs->getOffset());
        spriteData.origin   = legs->getOrigin();
        spriteData.flipX    = flipX;
        commandsOut.push_back({2, spriteData});
    }
}
