#include "roam.hpp"
#include "entity/entity.hpp"
#include "entity/metadata.hpp"
#include "math/random.hpp"

WuskkogelStateID WuskkogelRoamState::update(const UpdateContext &context)
{
    if (m_roamMoveTimer.completed())
    {
        moveDir.x = Math::Random::weakRandInt(-2, 3);
        moveDir.y = Math::Random::weakRandInt(-2, 3);
    }

    m_roamMoveTimer.update(context.context.dt);
    context.body.setVelocityTarget(moveDir.toFloat());

    uint64_t target = 0;
    const Entity *targetEntity = nullptr;
    for (auto &[id, entity] : context.context.nearbyEntities)
    {
        if (entity->getMetadata().type == EntityType::Player)
        {
            target = id;
            targetEntity = entity;
        }
    }

    if (target == 0)
    {
        return WuskkogelStateID::Roam;
    }

    WuskkogelStateID scanResultID = WuskkogelStateID::Roam;
    context.perception.scan(
        context.body.getPosition() + context.headPos, context.lookAngle,
        [&](Vec2i pos)
        {
            if (targetEntity->pointInside(pos))
            {
                scanResultID = WuskkogelStateID::Follow;
                r_targetID = target;
                return true;
            }

            if (const Particle *p =
                    context.context.particleHandler.getParticles().get(pos))
            {
                if (p->isSolid())
                {
                    return true;
                }
            }

            return false;
        });

    return scanResultID;
}
