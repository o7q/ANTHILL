#include "ai_movement_module.hpp"

#include "utils/math/numbers.hpp"

void AIMovementModule::update(Vec2<int> pos, const BoundingBox &box)
{
    m_shouldMove = false;
    m_shouldSetPosition = false;

    if (m_checkpoints.empty())
    {
        return;
    }

    AINavigationModule::Checkpoint current;
    while (true)
    {
        if (m_checkpoints.empty())
        {
            return;
        }

        current = m_checkpoints[0];

        bool breakout = false;

        switch (current.axis)
        {
        case AINavigationModule::Axis::Horizontal:
            if (current.pos.x >= box.getA().x + pos.x &&
                current.pos.x <= box.getB().x + pos.x)
            {
                m_checkpoints.erase(m_checkpoints.begin());
            }
            else
            {
                breakout = true;
            }
            break;
        case AINavigationModule::Axis::Vertical:
            if (current.pos.y >= box.getA().y + pos.y &&
                current.pos.y <= box.getB().y + pos.y)
            {
                m_checkpoints.erase(m_checkpoints.begin());
            }
            else
            {
                breakout = true;
            }
            break;
        }

        if (breakout)
        {
            break;
        }
    }

    if (m_previousCheckpoint.axis == AINavigationModule::Axis::Horizontal &&
        current.axis == AINavigationModule::Axis::Vertical)
    {
        // m_setPosition = current.pos;
        // m_shouldSetPosition = true;
    }
    else
    {
        int dirX = Utils::Math::Numbers::sign(current.pos.x - pos.x);
        int dirY = Utils::Math::Numbers::sign(current.pos.y - pos.y);
        m_moveDirection = {dirX, dirY};
        m_shouldMove = true;
    }

    m_previousCheckpoint = current;
}