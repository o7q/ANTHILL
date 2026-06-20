#include "ai_navigation.hpp"

std::optional<AINavigation::Checkpoint> AINavigation::get_next_movement_checkpoint(px::Vec2i currentPos)
{
    Checkpoint current;
    bool eatNext = true;
    while (eatNext)
    {
        if (m_checkpoints.empty())
        {
            return std::nullopt;
        }

        current = m_checkpoints[0];

        switch (current.axis)
        {
        case Axis::Horizontal:
            if (current.pos.x <= currentPos.x + m_config.checkpointEatRadius &&
                current.pos.x >= currentPos.x - m_config.checkpointEatRadius)
            {
                m_checkpoints.erase(m_checkpoints.begin());
            }
            else
            {
                eatNext = false;
            }
            break;
        case Axis::Vertical:
            if (current.pos.y <= currentPos.y + m_config.checkpointEatRadius &&
                current.pos.y >= currentPos.y - m_config.checkpointEatRadius)
            {
                m_checkpoints.erase(m_checkpoints.begin());
            }
            else
            {
                eatNext = false;
            }
            break;
        }
    }

    return current;
}

void AINavigation::update_movement(px::Vec2i currentPos)
{
    if (m_checkpoints.empty())
    {
        return;
    }

    // eat checkpoints
    std::optional<AINavigation::Checkpoint> current_opt = get_next_movement_checkpoint(currentPos);

    if (!current_opt.has_value())
    {
        return;
    }

    AINavigation::Checkpoint current = current_opt.value();

    if (current != m_previousCheckpoint)
    {
        m_stuckTimer.restart();
    }

    m_previousCheckpoint = current;

    px::Vec2i dir    = current.pos - currentPos;
    m_moveVector = dir;
}
