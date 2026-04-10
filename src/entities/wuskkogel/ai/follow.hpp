#pragma once

#include "ai/navigation/ai_navigation.hpp"
#include "ai/perception/ai_perception.hpp"
#include "ai/state_machine/state.hpp"
#include "backend/timer/timer.hpp"
#include "entities/wuskkogel/ai/states.hpp"
#include "entity/body/entity_body.hpp"
#include "entity/entity.hpp"

class WuskkogelFollowState : public State<WuskkogelStateID, UpdateContext>
{
  public:
    WuskkogelFollowState(uint64_t &targetID)
        : State(WuskkogelStateID::Follow), r_targetID(targetID)
    {
        m_targetLostTimer.setDurationInSeconds(5.0f);
        m_targetLostTimer.restart();
    }

    WuskkogelStateID update(const UpdateContext &context)
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

        context.navigation.setGoal(targetPos);
        if (targetPos != targetLastPos)
        {
        }

        context.navigation.update(context.body.getPosition(),
                                  context.worldContext);
        auto result = context.navigation.getMoveVector();

        if (result.has_value())
        {
            context.body.setVelocityTargetX(Math::Numbers::sign(result->x) *
                                            2.5f);
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

  private:
    uint64_t &r_targetID;

    Timer m_targetLostTimer;
};
