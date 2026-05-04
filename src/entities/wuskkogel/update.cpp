#include "events/entity/events.hpp"
#include "events/particle/events.hpp"
#include "wuskkogel.hpp"
#include <memory>

void Wuskkogel::update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
{
    m_lookAngle =
        Math::Angles::vectorsToAngle(m_body.getLastPositionFloat(), m_body.getPositionFloat()).degrees();

    for (DamageSource dd : m_damageSources)
    {
        auto pBleedEvent = std::make_unique<ParticleDrawEvent>();
        Particle blood;
        blood.setMatterType(Particle::MatterType::Liquid);
        blood.setPhysicsType(Particle::PhysicsType::Water);
        blood.setColor(Color(255, 0, 0, 220));
        blood.getVerlet().setVelocity(dd.direction * 10, context.time.dt);
        pBleedEvent->particle = blood;
        pBleedEvent->radius   = dd.amount / 2;
        pBleedEvent->position = dd.position;

        auto eBleedEvent = std::make_unique<EntityParticleEvent>(context.id, std::move(pBleedEvent));
        eventsOut.emit(std::move(eBleedEvent));

        m_health -= dd.amount;
    }

    UpdateContext updateContext{context,        eventsOut,   m_body,   m_aiPerception,
                                m_aiNavigation, m_lookAngle, m_headPos};
    m_damageSources.clear();

    m_stateMachine.update(updateContext);

    m_bodyHandler.update(context);
    m_animator.update(context.time.dt);
}
