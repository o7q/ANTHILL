#pragma once

#include "assets/assets.hpp"
#include "sprite/sprite_animator_group.hpp"

struct PlayerSprite
{
    enum class HeadAnimation
    {
        Idle,
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

    PlayerSprite(const Assets &assets);

    SpriteAnimatorGroup<HeadAnimation> head;
    SpriteAnimatorGroup<TorsoAnimation> torso;
    SpriteAnimatorGroup<LegsAnimation> legs;
};
