#include "a_star.hpp"

#include "backend/utils/vec.hpp"
#include "utils/data_structures/index_2d.hpp"
#include <unordered_map>

void AStarSolver::iteratePath(int amount)
{
    int i = 0;
    while (!m_toSearch.empty() && i < amount && !m_endReached)
    {
        if (m_iterations > m_maxIterations)
        {
            m_endReached = true;
            return;
        }

        m_current = m_toSearch.top();
        m_toSearch.pop();

        if (m_nodes[m_current.index].state == State::Closed)
        {
            continue;
        }

        m_nodes[m_current.index].state = State::Closed;

        if (m_current.index == Index2D(m_end.x, m_end.y))
        {
            m_endReached = true;
            return;
        }

        for (int i = 0; i < 8; ++i)
        {
            Index2D neighborIndex = {m_current.index.x + m_neighborX[i],
                                     m_current.index.y + m_neighborY[i]};

            if (!isNeighborWalkable(neighborIndex.x, neighborIndex.y))
            {
                continue;
            }

            AStarNode &neighbor = m_nodes[neighborIndex];
            float costToNeightbor =
                m_current.gCost + dist(m_current.index, neighborIndex);

            if (neighbor.state == State::Unvisited ||
                costToNeightbor < neighbor.gCost)
            {
                AStarNode next;
                next.index = neighborIndex;
                next.parentIndex = m_current.index;
                next.hasParent = true;
                next.state = State::Open;
                next.gCost = costToNeightbor;
                next.hCost = dist(neighborIndex, {m_end.x, m_end.y});
                next.calculateFCost();

                m_nodes[neighborIndex] = next;
                m_toSearch.push(next);
            }
        }

        ++i;
        ++m_iterations;
    }
}

// https://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html#diagonal-distance
float AStarSolver::dist(Index2D start, Index2D end)
{
    int dx = std::abs(end.x - start.x);
    int dy = std::abs(end.y - start.y);
    float D = 1.0f;
    float D2 = 1.4142f; // sqrt(2)
    return D * (dx + dy) + (D2 - 2.0f * D) * std::min(dx, dy);
    // return (dx + dy);
}
