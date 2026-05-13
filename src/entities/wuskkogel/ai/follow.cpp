#include "follow.hpp"

#include "entities/player/player.hpp"

WuskkogelStateID WuskkogelFollowState::update(const UpdateContext &context)
{
    if (m_targetLostTimer.completed())
    {
        return WuskkogelStateID::Roam;
    }

    m_targetLostTimer.update(context.context.time.dt);

    const Player *player = context.context.currentPlayer;

    if (!player)
    {
        return WuskkogelStateID::Roam;
    }

    Vec2i targetPos = player->getBody().getPosition();

    context.perception.scan(context.body.getPosition() + context.headPos, context.lookAngle,
                            [&](Vec2i pos)
                            {
                                if (player->getCollider().pointInsideAny(targetPos, pos))
                                {
                                    m_targetLostTimer.restart();
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

    context.navigation.setGoal(targetPos);

    context.navigation.update(context.body.getPosition(), context.context);
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