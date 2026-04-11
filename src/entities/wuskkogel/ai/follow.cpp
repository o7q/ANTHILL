#include "follow.hpp"
#include "entity/entity.hpp"

WuskkogelStateID WuskkogelFollowState::update(const UpdateContext &context)
{
    if (m_targetLostTimer.completed())
    {
        return WuskkogelStateID::Roam;
    }

    m_targetLostTimer.update(context.worldContext.dt);

    const Entity *targetEntity = nullptr;
    for (auto &[id, entity] : context.worldContext.nearbyEntities)
    {
        if (id == r_targetID)
        {
            targetEntity = entity;
        }
    }

    if (!targetEntity)
    {
        return WuskkogelStateID::Roam;
    }

    Vec2i targetPos = targetEntity->getBody().getPosition();
    Vec2i targetLastPos = targetEntity->getBody().getLastPosition();

    context.perception.scan(
        context.body.getPosition() + context.headPos, context.lookAngle,
        [&](Vec2i pos)
        {
            if (targetEntity->pointInside(pos))
            {
                m_targetLostTimer.restart();
                return true;
            }

            if (const Particle *p =
                    context.worldContext.world.getParticles().get(pos))
            {
                if (p->isSolid())
                {
                    return true;
                }
            }

            return false;
        });

    if (targetPos != targetLastPos)
    {
        context.navigation.setGoal(targetPos);
    }

    context.navigation.update(context.body.getPosition(), context.worldContext);
    auto result = context.navigation.getMoveVector();

    if (result.has_value())
    {
        context.body.setVelocityTargetX(Math::Numbers::sign(result->x) * 2.5f);
        context.body.setVelocityTargetY(Math::Numbers::sign(result->y) * 2);
    }

    Vec2i myPos = context.body.getPosition();

    int dx = std::abs(myPos.x - targetPos.x);
    int dy = std::abs(myPos.y - targetPos.y);

    if (dx + dy < 80)
    {
        return WuskkogelStateID::Attack;
    }

    return WuskkogelStateID::Follow;
}