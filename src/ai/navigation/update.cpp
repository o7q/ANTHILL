#include "ai_navigation.hpp"

void AINavigation::update(Vec2i currentPos,
                          const EntityWorldContext &worldContext)
{
    update_path(currentPos, worldContext);
    m_moveVector = std::nullopt;
    if (m_astarPathState == PathState::Ready)
    {
        update_movement(currentPos);
    }
}
