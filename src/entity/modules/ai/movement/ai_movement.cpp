#include "ai_movement.hpp"

#include "entity/modules/ai/navigation/ai_navigation.hpp"
#include "utils/math/numbers.hpp"

void AIMovement::update(Vec2<int> pos, const BoundingBox &box)
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
        case AINavigation::Axis::Vertical:
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

    if (m_previousCheckpoint.axis == AINavigation::Axis::Horizontal &&
        current.axis == AINavigation::Axis::Vertical)
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
