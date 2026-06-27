#include "roam.hpp"

#include "px/utils/random.hpp"
#include "entities/player/player.hpp"

WuskkogelStateID WuskkogelRoamState::update(const UpdateContext &context)
{
    if (m_roamMoveTimer.completed())
    {
        m_randomMoveDirection.x = px::Random::unseededRandomInt(-1, 2);
        m_randomMoveDirection.y = px::Random::unseededRandomInt(-1, 2);
    }

    context.body.setVelocityTarget(m_randomMoveDirection.toFloat());
    m_roamMoveTimer.update(context.context.time.getDeltaTime());

    const Player *player = context.context.currentPlayer;

    if (!player)
    {
        return WuskkogelStateID::Roam;
    }

    WuskkogelStateID scanResultID = WuskkogelStateID::Roam;
    context.perception.scan(
        context.body.getPosition() + context.headPos, context.lookAngle,
        [&](px::Vec2i pos)
        {
            if (player->getCollider().pointInsideAny(player->getBody().getPosition(), pos))
            {
                scanResultID = WuskkogelStateID::Follow;
                return true;
            }

            if (const Particle *p = context.context.particleHandler.getParticles().get(pos))
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
