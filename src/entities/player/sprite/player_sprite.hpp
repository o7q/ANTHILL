#pragma once

#include "assets/assets.hpp"
#include "entity/body/entity_body.hpp"
#include "sprite/sprite_animator_group.hpp"

class PlayerSprite
{
  public:
    enum class State
    {
        None,
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

  public:
    PlayerSprite(const Assets &assets);

    const SpriteAnimatorGroup<HeadAnimation> &getHead() const { return m_head; }
    const SpriteAnimatorGroup<TorsoAnimation> &getTorso() const
    {
        return m_torso;
    }
    const SpriteAnimatorGroup<LegsAnimation> &getLegs() const { return m_legs; }

    void update(const EntityBody &body, float lookAngle, float dt);

  private:
    State determine_state(const EntityBody &body);

    void update_head(State state, float lookAngle, float dt);
    void update_torso(State state, float dt);
    void update_legs(State state, float dt);

    void init_head(const Assets &assets);
    void init_torso(const Assets &assets);
    void init_legs(const Assets &assets);

  private:
    SpriteAnimatorGroup<HeadAnimation> m_head;
    SpriteAnimatorGroup<TorsoAnimation> m_torso;
    SpriteAnimatorGroup<LegsAnimation> m_legs;

    State m_lastState = State::None;
};
