#include "player_sprite.hpp"
#include "identifiers/assets/spritesheet.hpp"
#include "sprite/sprite_animator.hpp"
#include <utility>

PlayerSprite::PlayerSprite(const Assets &assets)
{
    auto makeAnimator = [&](SpriteSheetID id, unsigned int fps,
                            std::pair<int, int> origin, Vec2i offset)
    {
        SpriteAnimator animator(*assets.spriteSheets().get(id));
        animator.setFPS(fps);
        animator.setOrigin(origin);
        animator.setOffset(offset);
        return animator;
    };

    head.addAnimator(
        makeAnimator(SpriteSheetID::Entity_SumiIdleHead, 5, {4, 7}, {0, -4}),
        HeadAnimation::Idle);
    torso.addAnimator(
        makeAnimator(SpriteSheetID::Entity_SumiIdleTorso, 5, {2, 7}, {0, 3}),
        TorsoAnimation::Idle);
    legs.addAnimator(
        makeAnimator(SpriteSheetID::Entity_SumiIdleLegs, 5, {2, 7}, {0, 10}),
        LegsAnimation::Idle);

    head.addAnimator(
        makeAnimator(SpriteSheetID::Entity_SumiRunHead, 12, {3, 7}, {0, -4}),
        HeadAnimation::Run);
    torso.addAnimator(
        makeAnimator(SpriteSheetID::Entity_SumiRunTorso, 12, {5, 7}, {0, 3}),
        TorsoAnimation::Run);
    legs.addAnimator(
        makeAnimator(SpriteSheetID::Entity_SumiRunLegs, 12, {9, 8}, {0, 10}),
        LegsAnimation::Run);
}
