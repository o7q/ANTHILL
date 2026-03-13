#include "a_star.hpp"

#include "backend/utils/vec.hpp"
#include "utils/data_structures/index_2d.hpp"
#include <algorithm>
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
            Index2D neighborIndex = {
                m_current.index.x + M_NEIGHBOR_INDICIES_X[i],
                m_current.index.y + M_NEIGHBOR_INDICIES_Y[i]};

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

std::vector<Vec2<int>> AStarSolver::generatePath()
{
    std::vector<Vec2<int>> path;
    AStarNode *node = &m_nodes[m_current.index];
    while (node->hasParent)
    {
        path.push_back({node->index.x, node->index.y});
        node = &m_nodes[node->parentIndex];
    }
    path.push_back({node->index.x, node->index.y});
    std::reverse(path.begin(), path.end());

    return path;
}

void AStarSolver::reset(Vec2<int> start, Vec2<int> end)
{
    m_nodes.clear();
    m_toSearch = std::priority_queue<AStarNode, std::vector<AStarNode>,
                                     AStarNodeCompare>();

    m_start = start;
    m_end = end;

    m_endReached = false;

    m_iterations = 0;

    AStarNode startNode;
    startNode.index = Index2D(start.x, start.y);
    startNode.hCost = dist({start.x, start.y}, {end.x, end.y});
    startNode.calculateFCost();
    startNode.state = State::Open;

    m_nodes[startNode.index] = startNode;
    m_toSearch.push(startNode);
}
