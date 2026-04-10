#pragma once

#include "ai/state/state.hpp"
#include "backend/timer/timer.hpp"
#include "entities/wuskkogel/states/states.hpp"
#include "entity/body/entity_body.hpp"
#include "entity/entity.hpp"
#include "events/entity/entity_entity.hpp"
#include "math/numbers.hpp"
#include "math/random.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>

class WuskkogelAttackState : public State<WuskkogelStateID>
{
  public:
    WuskkogelAttackState(EntityBody &body, float &lookAngle, Vec2i &headPos,
                         uint64_t &targetID)
        : State(WuskkogelStateID::Attack), r_body(body), r_lookAngle(lookAngle),
          r_headPos(headPos), r_targetID(targetID)
    {
        m_attackTimer.setDurationInSeconds(0.5f);
    }

    WuskkogelStateID update(const EntityUpdateContext &context,
                            EventPool<EntityEvent> &eventsOut)
    {
        m_attackTimer.update(context.dt);

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

        Vec2f myPos = r_body.getPositionFloat();
        Vec2f targetPos = targetEntity->getBody().getPositionFloat();

        float dx = targetPos.x - myPos.x;
        float dy = targetPos.y - myPos.y;

        Vec2f vec = Vec2f(dx, dy).normalize() * 5.0f;

        if (!m_attackTimer.active())
        {
            r_body.setVelocity(vec);
            m_attackTimer.restart();
            m_bit = false;
        }

        if (std::abs(dx) + std::abs(dy) < 10 && !m_bit)
        {
            std::cout << "BITE!" << std::endl;
            auto damageEvent = std::make_unique<EntityDamageEvent>(context.id);
            damageEvent->target = target;
            damageEvent->damage = 5;
            eventsOut.emit(std::move(damageEvent));
            m_bit = true;
        }

        if (std::abs(dx) + std::abs(dy) > 70)
        {
            return WuskkogelStateID::Follow;
        }

        return WuskkogelStateID::Attack;
    }

  private:
    EntityBody &r_body;
    float &r_lookAngle;
    Vec2i &r_headPos;
    uint64_t &r_targetID;

    bool m_bit = false;

    Timer m_attackTimer;
};
