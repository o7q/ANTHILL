#include "identifiers/spritesheet.hpp"
#include "player_sprite.hpp"
#include "sprite/sprite_animator.hpp"
#include <utility>

PlayerSprite::PlayerSprite(const Assets &assets)
{
    init_head(assets);
    init_torso(assets);
    init_legs(assets);
}

void PlayerSprite::init_head(const Assets &assets)
{
    m_head.addAnimator(
        HeadAnimation::Idle,
        {{assets.spriteSheets().get(SpriteSheetID::Entity_SumiStaticHead), 1}, {4, 6}, {0, -4}});
    m_head.addAnimator(
        HeadAnimation::IdleUp45,
        {{assets.spriteSheets().get(SpriteSheetID::Entity_SumiStaticHeadUp45), 1}, {5, 7}, {0, -3}});
    m_head.addAnimator(
        HeadAnimation::IdleDown45,
        {{assets.spriteSheets().get(SpriteSheetID::Entity_SumiStaticHeadDown45), 1}, {2, 7}, {0, -3}});

    m_head.addAnimator(HeadAnimation::Run,
                       {{assets.spriteSheets().get(SpriteSheetID::Entity_SumiRunHead), 12}, {3, 7}, {0, -4}});
    m_head.addAnimator(
        HeadAnimation::RunUp45,
        {{assets.spriteSheets().get(SpriteSheetID::Entity_SumiRunHeadUp45), 12}, {5, 8}, {0, -3}});
    m_head.addAnimator(
        HeadAnimation::RunDown45,
        {{assets.spriteSheets().get(SpriteSheetID::Entity_SumiRunHeadDown45), 12}, {2, 8}, {0, -3}});
}

void PlayerSprite::init_torso(const Assets &assets)
{
    m_torso.addAnimator(
        TorsoAnimation::Idle,
        {{assets.spriteSheets().get(SpriteSheetID::Entity_SumiIdleTorso), 1}, {2, 6}, {0, 3}});
    m_torso.addAnimator(
        TorsoAnimation::Run,
        {{assets.spriteSheets().get(SpriteSheetID::Entity_SumiRunTorso), 12}, {5, 7}, {0, 3}});
}

void PlayerSprite::init_legs(const Assets &assets)
{
    m_legs.addAnimator(
        LegsAnimation::Idle,
        {{assets.spriteSheets().get(SpriteSheetID::Entity_SumiStaticLegs), 1}, {1, 7}, {0, 10}});
    m_legs.addAnimator(LegsAnimation::Run,
                       {{assets.spriteSheets().get(SpriteSheetID::Entity_SumiRunLegs), 12}, {9, 8}, {0, 10}});
}
