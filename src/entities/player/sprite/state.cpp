#include "player_sprite.hpp"

PlayerSprite::State PlayerSprite::determine_state(const EntityBody &body)
{
    if (std::abs(body.getVelocity().x) > 0.2f && body.getPosition().x - body.getLastPosition().x != 0)
    {
        return State::Run;
    }
    else
    {
        return State::Idle;
    }
}
