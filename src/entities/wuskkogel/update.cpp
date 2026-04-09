#include "math/angle.hpp"
#include "world/particle_world/particle.hpp"
#include "wuskkogel.hpp"
#include <iostream>

void Wuskkogel::update(const EntityUpdateContext &context,
                       EventPool<EntityEvent> &eventsOut)
{
    // std::cout << static_cast<int>(m_state) << std::endl;

    if (m_targetLostTimer.completed())
    {
        m_state = State::Idle;
    }

    m_targetLostTimer.update(context.dt);
    m_targetRecalcTimer.update(context.dt);

    switch (m_state)
    {
    case State::Idle:
        update_idle(context, eventsOut);
        break;
    case State::Follow:
        update_follow(context, eventsOut);
        break;
    case State::Attack:
        break;
    case State::Flee:
        break;
    }

    m_bodyHandler.update(context);
    m_animator.update(context.dt);
}

void Wuskkogel::update_idle(const EntityUpdateContext &context,
                            EventPool<EntityEvent> &eventsOut)
{
    const Entity *player = context.currentPlayer;

    if (!player)
    {
        return;
    }

    m_aiPerception.checkForInterestsInSight(
        m_body.getPosition() + m_headPos, m_lookAngle,
        [&](Vec2i pos)
        {
            if (player->getBoundingBox().pointInside(
                    pos - player->getBody().getPosition()))
            {
                m_state = State::Follow;
                p_target = player;
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

    m_lookAngle += 1.0f;
}
void Wuskkogel::update_follow(const EntityUpdateContext &context,
                              EventPool<EntityEvent> &eventsOut)
{
    if (!p_target)
    {
        m_state = State::Idle;
        return;
    }

    Vec2i targetPos = p_target->getBody().getPosition();
    m_lookAngle = Math::Angles::vectorsToAngle(m_body.getPosition().toFloat(),
                                               targetPos.toFloat())
                      .degrees();

    m_aiPerception.checkForInterestsInSight(
        m_body.getPosition() + m_headPos, m_lookAngle,
        [&](Vec2i pos)
        {
            if (p_target->getBoundingBox().pointInside(pos - targetPos))
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

    // if (m_state == State::Idle)
    // {
    //     return;
    // }

    if (targetPos != p_target->getBody().getLastPosition() ||
        m_targetRecalcTimer.completed())
    {
        m_aiNavigation.setGoal(targetPos);
    }

    if (m_targetRecalcTimer.completed())
    {
        std::cout << "yo" << std::endl;
    }

    m_aiNavigation.update(m_body.getPosition(), context);

    auto result = m_aiNavigation.getMoveVector();

    if (result.has_value())
    {
        m_body.setVelocityTargetX(Math::Numbers::sign(result->x) * 1.5f);
        m_body.setVelocityTargetY(Math::Numbers::sign(result->y) * 1);
    }
}
void Wuskkogel::update_attack(const EntityUpdateContext &context,
                              EventPool<EntityEvent> &eventsOut)
{
}
void Wuskkogel::update_flee(const EntityUpdateContext &context,
                            EventPool<EntityEvent> &eventsOut)
{
}
