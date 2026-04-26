#include "player_sprite.hpp"

PlayerSprite::PlayerSprite(const Assets &assets)
{
    init_run(assets);
    init_idle(assets);
}

void PlayerSprite::init_run(const Assets &assets)
{
    SpriteAnimator headAnimation(
        *assets.spriteSheets().get(SpriteSheetID::Entity_SumiRunHead));
    headAnimation.setFPS(12);
    headAnimation.setOrigin({3, std::nullopt});
    add_animation(PlayerBodyPart::Head, PlayerAnimation::Run, headAnimation);

    SpriteAnimator torsoAnimation(
        *assets.spriteSheets().get(SpriteSheetID::Entity_SumiRunTorso));
    torsoAnimation.setFPS(12);
    headAnimation.setOrigin({1, 0});
    add_animation(PlayerBodyPart::Torso, PlayerAnimation::Run, torsoAnimation);

    SpriteAnimator legsAnimation(
        *assets.spriteSheets().get(SpriteSheetID::Entity_SumiRunLegs));
    legsAnimation.setFPS(12);
    legsAnimation.setOrigin({9, 0});
    add_animation(PlayerBodyPart::Legs, PlayerAnimation::Run, legsAnimation);
}

void PlayerSprite::init_idle(const Assets &assets)
{
    SpriteAnimator headAnimation(
        *assets.spriteSheets().get(SpriteSheetID::Entity_SumiIdleHead));
    headAnimation.setFPS(5);
    headAnimation.setOrigin({4, 14});
    headAnimation.setOffset({0, 3});
    add_animation(PlayerBodyPart::Head, PlayerAnimation::Idle, headAnimation);

    SpriteAnimator torsoAnimation(
        *assets.spriteSheets().get(SpriteSheetID::Entity_SumiIdleTorso));
    torsoAnimation.setFPS(5);
    torsoAnimation.setOrigin({1, 7});
    torsoAnimation.setOffset({0, 3});
    add_animation(PlayerBodyPart::Torso, PlayerAnimation::Idle, torsoAnimation);

    SpriteAnimator legsAnimation(
        *assets.spriteSheets().get(SpriteSheetID::Entity_SumiIdleLegs));
    legsAnimation.setFPS(5);
    legsAnimation.setOrigin({2, 0});
    legsAnimation.setOffset({0, 3});
    add_animation(PlayerBodyPart::Legs, PlayerAnimation::Idle, legsAnimation);
}
