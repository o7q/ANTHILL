#include "ai_navigation.hpp"

void AINavigation::update(Vec2i currentPos, const EntityUpdateContext &context)
{
    update_path(currentPos, context);
    m_moveVector = std::nullopt;
    if (m_astarPathState == PathState::Ready)
    {
        update_movement(currentPos);
    }

    m_stuckTimer.update(context.time.dt);
}
