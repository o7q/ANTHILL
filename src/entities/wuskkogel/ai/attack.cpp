#include "attack.hpp"
#include "entity/entity.hpp"
#include "events/entity/entity_entity.hpp"

WuskkogelStateID WuskkogelAttackState::update(const UpdateContext &context)
{
    m_attackTimer.update(context.worldContext.dt);

    uint64_t target = 0;
    const Entity *targetEntity = nullptr;
    for (auto &[id, entity] : context.worldContext.nearbyEntities)
    {
        if (id == r_targetID)
        {
            target = id;
            targetEntity = entity;
        }
    }

    if (!targetEntity)
    {
        return WuskkogelStateID::Roam;
    }

    Vec2f myPos = context.body.getPositionFloat();
    Vec2f targetPos = targetEntity->getBody().getPositionFloat();

    float dx = targetPos.x - myPos.x;
    float dy = targetPos.y - myPos.y;

    Vec2f vec = Vec2f(dx, dy).normalize() * 8.0f;

    if (!m_attackTimer.active())
    {
        context.body.setVelocity(vec);
        m_attackTimer.restart();
        m_bit = false;
    }

    if (std::abs(dx) + std::abs(dy) < 10 && !m_bit)
    {
        auto damageEvent =
            std::make_unique<EntityDamageEvent>(context.worldContext.id);
        damageEvent->target = target;
        damageEvent->damage = 5;
        context.events.emit(std::move(damageEvent));
        m_bit = true;
    }

    if (std::abs(dx) + std::abs(dy) > 100)
    {
        return WuskkogelStateID::Follow;
    }

    return WuskkogelStateID::Attack;
}
