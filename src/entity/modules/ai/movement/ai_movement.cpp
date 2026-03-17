#include "ai_movement.hpp"

#include "entity/modules/ai/navigation/ai_navigation.hpp"
#include "math/numbers.hpp"

void AIMovement::update(Vec2<int> pos, const StaticGridRectangle &bb)
{
    m_shouldMove = false;
    m_shouldSetPosition = false;

    if (m_checkpoints.empty())
    {
        return;
    }

    AINavigation::Checkpoint current;
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
        case AINavigation::Axis::Horizontal:
            if (current.pos.x >= bb.getA().x + pos.x &&
                current.pos.x <= bb.getB().x + pos.x)
            {
                m_checkpoints.erase(m_checkpoints.begin());
            }
            else
            {
                breakout = true;
            }
            break;
        case AINavigation::Axis::Vertical:
            if (current.pos.y >= bb.getA().y + pos.y &&
                current.pos.y <= bb.getB().y + pos.y)
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

    if (m_previousCheckpoint.axis == AINavigation::Axis::Horizontal &&
        current.axis == AINavigation::Axis::Vertical)
    {
        // m_setPosition = current.pos;
        // m_shouldSetPosition = true;
    }
    else
    {
        int dirX = Math::Numbers::sign(current.pos.x - pos.x);
        int dirY = Math::Numbers::sign(current.pos.y - pos.y);
        m_moveDirection = {dirX, dirY};
        m_shouldMove = true;
    }

    m_previousCheckpoint = current;
}
