#include "wuskkogel.hpp"

void Wuskkogel::update(const EntityUpdateContext &context,
                       EventPool<EntityEvent> &eventsOut)
{
    m_lookAngle = Math::Angles::vectorsToAngle(m_body.getLastPositionFloat(),
                                               m_body.getPositionFloat())
                      .degrees();

    UpdateContext updateContext{context,        eventsOut,      m_body,
                                m_aiPerception, m_aiNavigation, m_lookAngle,
                                m_headPos};

    m_stateMachine.update(updateContext);

    m_bodyHandler.update(context);
    m_animator.update(context.dt);
}
