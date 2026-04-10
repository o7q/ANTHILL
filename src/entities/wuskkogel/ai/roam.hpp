#pragma once

#include "ai/perception/ai_perception.hpp"
#include "ai/state_machine/state.hpp"
#include "backend/timer/timer.hpp"
#include "entities/wuskkogel/ai/states.hpp"
#include "entity/body/entity_body.hpp"
#include "entity/entity.hpp"
#include "math/random.hpp"

class WuskkogelRoamState : public State<WuskkogelStateID, UpdateContext>
{
  public:
    WuskkogelRoamState(uint64_t &targetID)
        : State(WuskkogelStateID::Roam), r_targetID(targetID)
    {
        m_roamMoveTimer.setDurationInSeconds(1.0f);
        m_roamMoveTimer.setMode(Timer::Mode::Repeat);
        m_roamMoveTimer.restart();
    }

    WuskkogelStateID update(const UpdateContext &context)
    {
        if (m_roamMoveTimer.completed())
        {
            moveDir.x = Math::Random::weakRandInt(-2, 3);
            moveDir.y = Math::Random::weakRandInt(-2, 3);
        }

        m_roamMoveTimer.update(context.worldContext.dt);
        context.body.setVelocityTarget(moveDir.toFloat());

        uint64_t target = 0;
        const Entity *targetEntity = nullptr;
        for (auto &[id, entity] : context.worldContext.nearbyEntities)
        {
            if (entity->getMetadata().faction == EntityFaction::Player)
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
                        context.worldContext.world.getParticles().get(pos))
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

  private:
    uint64_t &r_targetID;

    Vec2i moveDir;
    Timer m_roamMoveTimer;
};
