#include "ai_navigation.hpp"

void AINavigation::update_path(Vec2i currentPos,
                               const EntityUpdateContext &context)
{
    Index2D end =
        context.particleHandler.getNavmesh().getIndexFromWorldPosition(
            m_astarGoalPosition);
    if (Vec2i(end.x, end.y) != m_astar.getEnd() || m_isStuck)
    {
        Index2D start =
            context.particleHandler.getNavmesh().getIndexFromWorldPosition(
                currentPos);
        m_astar.reset(Vec2i(start.x, start.y), {end.x, end.y});
        m_checkpoints.clear();
        m_astarPathState = PathState::Iterating;
        m_isStuck = false;
        m_stuckCounter = 0;
    }

    if (m_astarPathState != PathState::Iterating)
    {
        return;
    }

    if (!m_astar.endReached())
    {
        m_astar.iteratePath(
            m_config.astarIterationsPerFrame,
            [context, check = m_config.astarNeighborCheckFunction](int x, int y)
            { return check(context, Index2D(x, y)); });
    }
    else
    {
        std::vector<Vec2i> positions = m_astar.generatePath();

        Vec2i last;
        for (Vec2i pos : positions)
        {
            int dx = std::abs(pos.x - last.x);
            int dy = std::abs(pos.y - last.y);

            bool xChanged = dx != 0;
            bool yChanged = dy != 0;

            Axis axis = Axis::Horizontal;
            if (yChanged && !xChanged)
            {
                axis = Axis::Vertical;
            }

            m_checkpoints.push_back({pos * context.particleHandler.getNavmesh()
                                               .getResolution()
                                               .toInt(),
                                     axis});
            last = pos;
        }

        m_astarPathState = PathState::Ready;
    }
}
