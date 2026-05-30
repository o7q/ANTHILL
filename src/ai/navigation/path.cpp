#include "ai_navigation.hpp"

#include "core/math/distance.hpp"

void AINavigation::update_path(Vec2i currentPos, const EntityUpdateContext &context)
{
    Vec2i end = context.particleHandler.getNavmesh().getIndexFromWorldPosition(m_astarGoalPosition);

    float goalDist = Math::Distance::euclidian(currentPos.toFloat(), m_astarGoalPosition.toFloat());
    if (end != m_astar.getEnd() || (m_stuckTimer.completed() && goalDist > m_config.satisfactoryDistance))
    {
        Vec2i start = context.particleHandler.getNavmesh().getIndexFromWorldPosition(currentPos);
        m_astar.reset(start, end);
        m_checkpoints.clear();
        m_stuckTimer.restart();
        m_astarPathState = PathState::Iterating;
    }

    if (m_astarPathState != PathState::Iterating)
    {
        return;
    }

    m_astar.iteratePath(m_config.iterationsPerFrame, [context, check = m_config.astarNeighborCheckFunction](
                                                         int x, int y) { return check(context, {x, y}); });

    if (m_astar.pathFound())
    {
        std::vector<Vec2i> checkpointPositions = m_astar.generatePath();

        Vec2i lastCheckpointPos;
        for (Vec2i checkpointPos : checkpointPositions)
        {
            int dx = std::abs(checkpointPos.x - lastCheckpointPos.x);
            int dy = std::abs(checkpointPos.y - lastCheckpointPos.y);

            bool xChanged = dx != 0;
            bool yChanged = dy != 0;

            Axis axis = Axis::Horizontal;
            if (yChanged && !xChanged)
            {
                axis = Axis::Vertical;
            }

            m_checkpoints.push_back(
                {checkpointPos * context.particleHandler.getNavmesh().getResolution().toInt(), axis});
            lastCheckpointPos = checkpointPos;
        }

        m_astarPathState = PathState::Ready;
    }
}
