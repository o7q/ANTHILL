#include "wuskkogel.hpp"

EventPool<EntityEvent> Wuskkogel::update(const EntityUpdateContext &context)
{
    EventPool<EntityEvent> events;

    const Entity *player = nullptr;
    for (const Entity *entity : context.nearbyEntities)
    {
        if (entity->getMetadata().faction == EntityFaction::Player)
        {
            player = entity;
            break;
        }
    }

    if (!player)
    {
        return events;
    }

    Vec2i playerPos = player->getBody().getPosition();

    if (playerPos != player->getBody().getLastPosition())
    {
        m_aiNavigation.setGoal(player->getBody().getPosition());
    }

    m_aiNavigation.update(m_body.getPosition(), context);

    auto result = m_aiNavigation.getMoveVector();

    if (result.has_value())
    {
        m_body.setVelocityTargetX(Math::Numbers::sign(result->x) * 1.5f);
        m_body.setVelocityTargetY(Math::Numbers::sign(result->y) * 1);
    }

    m_bodyHandler.update(context);
    m_animator.update(context.dt);

    return events;
}
