#pragma once

#include "assets/assets.hpp"
#include "sprite/sprite_animator_group.hpp"

struct PlayerSprite
{
    enum class GlobalState
    {
        Idle,
        Run
    };

    enum class HeadAnimation
    {
        Idle,
        IdleUp45,
        IdleDown45,
        Run
    };
    enum class TorsoAnimation
    {
        Idle,
        Run
    };
    enum class LegsAnimation
    {
        Idle,
        Run
    };

    void update(float dt)
    {
        head.update(dt);
        torso.update(dt);
        legs.update(dt);
    }

    void switchToRun()
    {
        m_sprite.head.switchAnimator(PlayerSprite::HeadAnimation::Run);
        m_sprite.torso.switchAnimator(PlayerSprite::TorsoAnimation::Run);
        m_sprite.legs.switchAnimator(PlayerSprite::LegsAnimation::Run);
    }

    PlayerSprite(const Assets &assets);

    SpriteAnimatorGroup<HeadAnimation> head;
    SpriteAnimatorGroup<TorsoAnimation> torso;
    SpriteAnimatorGroup<LegsAnimation> legs;
};
