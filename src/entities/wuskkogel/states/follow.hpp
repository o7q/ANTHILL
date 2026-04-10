#pragma once

#include "ai/navigation/ai_navigation.hpp"
#include "ai/perception/ai_perception.hpp"
#include "ai/state/state.hpp"
#include "backend/timer/timer.hpp"
#include "entities/wuskkogel/states/states.hpp"
#include "entity/body/entity_body.hpp"
#include "entity/entity.hpp"

class WuskkogelFollowState : public State<WuskkogelStateID>
{
  public:
    WuskkogelFollowState(EntityBody &body, AIPerception &aiPerception,
                         AINavigation &aiNavigation, float &lookAngle,
                         Vec2i &headPos, uint64_t &targetID)
        : State(WuskkogelStateID::Follow), r_body(body),
          r_aiPerception(aiPerception), r_aiNavigation(aiNavigation),
          r_lookAngle(lookAngle), r_headPos(headPos), r_targetID(targetID)
    {
        m_targetLostTimer.setDurationInSeconds(5.0f);
        m_targetLostTimer.restart();
    }

    WuskkogelStateID update(const EntityUpdateContext &context,
                            EventPool<EntityEvent> &eventsOut)
    {
        if (m_targetLostTimer.completed())
        {
            return WuskkogelStateID::Roam;
        }

        m_targetLostTimer.update(context.dt);

        uint64_t target = 0;
        const Entity *targetEntity = nullptr;
        for (auto &[id, entity] : context.nearbyEntities)
        {
            if (id == r_targetID)
            {
                target = id;
                targetEntity = entity;
            }
        }

        if (target == 0)
        {
            return WuskkogelStateID::Roam;
        }

        Vec2i targetPos = targetEntity->getBody().getPosition();
        Vec2i targetLastPos = targetEntity->getBody().getLastPosition();

        r_lookAngle =
            Math::Angles::vectorsToAngle(r_body.getLastPositionFloat(),
                                         r_body.getPositionFloat())
                .degrees();

        r_aiPerception.scan(
            r_body.getPosition() + r_headPos, r_lookAngle,
            [&](Vec2i pos)
            {
                if (targetEntity->getBoundingBox().pointInside(pos - targetPos))
                {
                    m_targetLostTimer.restart();
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

            r_aiNavigation.setGoal(targetPos);
        if (targetPos != targetLastPos)
        {
        }

        r_aiNavigation.update(r_body.getPosition(), context);
        auto result = r_aiNavigation.getMoveVector();

        if (result.has_value())
        {
            r_body.setVelocityTargetX(Math::Numbers::sign(result->x) * 1.5f);
            r_body.setVelocityTargetY(Math::Numbers::sign(result->y) * 1);
        }

        Vec2i myPos = r_body.getPosition();

        int dx = std::abs(myPos.x - targetPos.x);
        int dy = std::abs(myPos.y - targetPos.y);

        if (dx + dy < 50)
        {
            return WuskkogelStateID::Attack;
        }

        return WuskkogelStateID::Follow;
    }

  private:
    EntityBody &r_body;
    AIPerception &r_aiPerception;
    AINavigation &r_aiNavigation;
    float &r_lookAngle;
    Vec2i &r_headPos;
    uint64_t &r_targetID;

    Timer m_targetLostTimer;
};
