#pragma once

#include "ai/perception/ai_perception.hpp"
#include "ai/state/state.hpp"
#include "backend/timer/timer.hpp"
#include "entities/wuskkogel/states/states.hpp"
#include "entity/body/entity_body.hpp"
#include "entity/entity.hpp"
#include "entity/metadata.hpp"
#include "math/random.hpp"

class WuskkogelRoamState : public State<WuskkogelStateID>
{
  public:
    WuskkogelRoamState(EntityBody &body, AIPerception &aiPerception,
                       float &lookAngle, Vec2i &headPos, uint64_t &targetID)
        : State(WuskkogelStateID::Roam), r_body(body),
          r_aiPerception(aiPerception), r_lookAngle(lookAngle),
          r_headPos(headPos), r_targetID(targetID)
    {
        m_roamMoveTimer.setDurationInSeconds(1.0f);
        m_roamMoveTimer.setMode(Timer::Mode::Repeat);
        m_roamMoveTimer.restart();
    }

    WuskkogelStateID update(const EntityUpdateContext &context,
                            EventPool<EntityEvent> &eventsOut)
    {
        if (m_roamMoveTimer.completed())
        {
            moveDir.x = Math::Random::weakRandInt(-1, 2);
            moveDir.y = Math::Random::weakRandInt(-1, 2);
        }

        m_roamMoveTimer.update(context.dt);
        r_body.setVelocityTarget(moveDir.toFloat());

        uint64_t target = 0;
        const Entity *targetEntity = nullptr;
        for (auto &[id, entity] : context.nearbyEntities)
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

        r_aiPerception.scan(
            r_body.getPosition() + r_headPos, r_lookAngle,
            [&](Vec2i pos)
            {
                if (targetEntity->getBoundingBox().pointInside(
                        pos - targetEntity->getBody().getPosition()))
                {
                    scanResultID = WuskkogelStateID::Follow;
                    r_targetID = target;
                    return true;
                }

                if (const Particle *p = context.world.getParticles().get(pos))
                {
                    if (p->isSolid())
                    {
                        return true;
                    }
                }

                return false;
            });

        r_lookAngle =
            Math::Angles::vectorsToAngle(r_body.getLastPositionFloat(),
                                         r_body.getPositionFloat())
                .degrees();

        return scanResultID;
    }

  private:
    EntityBody &r_body;
    AIPerception &r_aiPerception;
    float &r_lookAngle;
    Vec2i &r_headPos;
    uint64_t &r_targetID;

    Vec2i moveDir;
    Timer m_roamMoveTimer;
};
