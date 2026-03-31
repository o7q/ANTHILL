#include "wuskkogel.hpp"

void Wuskkogel::update(const EntityUpdateContext &context)
{
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
        return;
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
        m_body.setVelocityY(Math::Numbers::sign(result->y));
        m_body.setVelocityX(Math::Numbers::sign(result->x) * 1);
    }
    else
    {
        m_body.setVelocityX(0);
    }

    updateMotion(context);
    updateHealth();

    m_animator.update(context.dt);
}