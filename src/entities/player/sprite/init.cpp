#include "identifiers/assets/spritesheet.hpp"
#include "player_sprite.hpp"
#include "sprite/sprite_animator.hpp"
#include "sprite/sprite_animator_group.hpp"
#include <utility>

PlayerSprite::PlayerSprite(const Assets &assets)
{
    init_head(assets);
    init_torso(assets);
    init_legs(assets);

    m_head.switchAnimator(HeadAnimation::Idle);
    m_torso.switchAnimator(TorsoAnimation::Idle);
    m_legs.switchAnimator(LegsAnimation::Idle);
}

void PlayerSprite::init_head(const Assets &assets)
{
    m_head.addAnimator(
        {*assets.spriteSheets().get(SpriteSheetID::Entity_SumiHead),
         1,
         {4, 6},
         {0, -4}},
        HeadAnimation::Idle);

    m_head.addAnimator(
        {*assets.spriteSheets().get(SpriteSheetID::Entity_SumiHeadUp45),
         1,
         {5, 7},
         {0, -3}},
        HeadAnimation::IdleUp45);

    m_head.addAnimator(
        {*assets.spriteSheets().get(SpriteSheetID::Entity_SumiHeadDown45),
         1,
         {2, 7},
         {0, -3}},
        HeadAnimation::IdleDown45);

    m_head.addAnimator(
        {*assets.spriteSheets().get(SpriteSheetID::Entity_SumiRunHead),
         12,
         {3, 7},
         {0, -4}},
        HeadAnimation::Run);
}

void PlayerSprite::init_torso(const Assets &assets)
{
    m_torso.addAnimator(
        {*assets.spriteSheets().get(SpriteSheetID::Entity_SumiIdleTorso),
         1,
         {2, 6},
         {0, 3}},
        TorsoAnimation::Idle);

    m_torso.addAnimator(
        {*assets.spriteSheets().get(SpriteSheetID::Entity_SumiRunTorso),
         12,
         {5, 7},
         {0, 3}},
        TorsoAnimation::Run);
}

void PlayerSprite::init_legs(const Assets &assets)
{
    m_legs.addAnimator(
        {*assets.spriteSheets().get(SpriteSheetID::Entity_SumiIdleLegs),
         1,
         {1, 7},
         {0, 10}},
        LegsAnimation::Idle);

    m_legs.addAnimator(
        {*assets.spriteSheets().get(SpriteSheetID::Entity_SumiRunLegs),
         12,
         {9, 8},
         {0, 10}},
        LegsAnimation::Run);
}
