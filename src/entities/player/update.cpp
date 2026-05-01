#include "player.hpp"

void Player::update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
{
    update_movement(context, eventsOut);
    update_items(context, eventsOut);

    m_sprite.update({m_body, m_angle, false, false, false}, context.time.dt);
}
