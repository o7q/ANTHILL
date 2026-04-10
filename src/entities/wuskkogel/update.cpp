#include "entities/wuskkogel/states/attack.hpp"
#include "entities/wuskkogel/states/follow.hpp"
#include "entities/wuskkogel/states/roam.hpp"
#include "entities/wuskkogel/states/states.hpp"
#include "wuskkogel.hpp"

void Wuskkogel::update(const EntityUpdateContext &context,
                       EventPool<EntityEvent> &eventsOut)
{
    update_state(context, eventsOut);

    m_bodyHandler.update(context);
    m_animator.update(context.dt);
}

void Wuskkogel::update_state(const EntityUpdateContext &context,
                             EventPool<EntityEvent> &eventsOut)
{
    
    if (!m_currentState)
    {
        return;
    }
    
    WuskkogelStateID state = m_currentState->update(context, eventsOut);
    // std::cout << (int)state << std::endl;

    if (state != m_currentState->getSelfID())
    {
        switch (state)
        {
        case WuskkogelStateID::Follow:
            m_currentState = std::make_unique<WuskkogelFollowState>(
                m_body, m_aiPerception, m_aiNavigation, m_lookAngle, m_headPos,
                m_targetID);
            break;
        case WuskkogelStateID::Roam:
            m_currentState = std::make_unique<WuskkogelRoamState>(
                m_body, m_aiPerception, m_lookAngle, m_headPos, m_targetID);
            break;
        case WuskkogelStateID::Attack:
            m_currentState = std::make_unique<WuskkogelAttackState>(
                m_body, m_lookAngle, m_headPos, m_targetID);
            break;
        }
    }
}
