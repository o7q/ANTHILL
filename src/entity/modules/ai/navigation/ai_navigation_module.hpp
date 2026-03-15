#pragma once

#include "utils/pathfinding/a_star.hpp"

class AINavigationModule
{
  public:
    enum class PathState
    {
        Idle,
        Iterating,
        Ready
    };

    enum class Axis
    {
        Vertical,
        Horizontal
    };

    struct Checkpoint
    {
        Vec2<int> pos;
        Axis axis;
    };

  public:
    AINavigationModule() {}

    template <typename NeighborCheckFunction>
    void update(float dt, NeighborCheckFunction &&checkFunction)
    {
        if (!m_astar.endReached() && m_pathState == PathState::Iterating)
        {
            m_astar.iteratePath(m_astarSubIterateAmount, checkFunction);
        }

        if (m_astar.endReached() && m_pathState == PathState::Iterating)
        {
            std::vector<Vec2<int>> positions = m_astar.generatePath();

            Vec2<int> last;
            for (Vec2<int> pos : positions)
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

                m_checkpoints.push_back({pos, axis});
                last = pos;
            }

            m_pathState = PathState::Ready;
        }
    }

    void setGoal(Vec2<int> start, Vec2<int> end)
    {
        m_startPos = start;
        m_endPos = end;
        m_astar.reset(start, end);
        m_checkpoints.clear();
        m_pathState = PathState::Iterating;
    }

    void sleep() { m_pathState = PathState::Idle; }

    void setAStarMaxIterations(int maxIterations)
    {
        m_astar.setMaxIterations(maxIterations);
    }

    void setAStarTerminationDistance(int distance)
    {
        m_astar.setTerminateDistance(distance);
    }

    void setAStarSubIterateAmount(int subIterateAmount)
    {
        m_astarSubIterateAmount = subIterateAmount;
    }

    const std::vector<Checkpoint> &getCheckpoints() const
    {
        return m_checkpoints;
    }

    PathState getPathState() const { return m_pathState; }

  private:
    AStarSolver m_astar;
    int m_astarSubIterateAmount = 1000;

    PathState m_pathState = PathState::Idle;

    std::vector<Checkpoint> m_checkpoints;

    Vec2<int> m_startPos;
    Vec2<int> m_endPos;
};
