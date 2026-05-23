#pragma once

#include "a_star_neighbors.hpp"
#include "core/ai/a_star_node.hpp"
#include "core/math/geometry/vec.hpp"
#include <cstdlib>
#include <queue>
#include <vector>

class AStarSolver
{
  public:
    struct Config
    {
        int maxIterations   = 50000;
        int endCutoffAmount = 0;
    };

  public:
    AStarSolver() { reset(Vec2i(0, 0), Vec2i(0, 0)); }
    virtual ~AStarSolver() = default;

    void reset(Vec2i start, Vec2i end);

    template <typename NeighborCheckFunction>
    void iteratePath(int amount, NeighborCheckFunction &&checkFunction)
    {
        int localIterations = 0;
        while (!m_toSearch.empty() && localIterations < amount && !m_pathFound)
        {
            if (m_iterationCount > m_config.maxIterations)
            {
                return;
            }

            m_current = m_toSearch.top();
            m_toSearch.pop();

            if (m_nodes[m_current.index].state == AStarNode::State::Closed)
            {
                continue;
            }

            m_nodes[m_current.index].state = AStarNode::State::Closed;

            bool terminate = false;

            if (m_config.endCutoffAmount > 0)
            {
                int distanceToEnd =
                    std::abs(m_current.index.x - m_end.x) + std::abs(m_current.index.y - m_end.y);

                if (distanceToEnd < m_config.endCutoffAmount)
                {
                    terminate = true;
                }
            }

            if (m_current.index == m_end || terminate)
            {
                m_pathFound = true;
                return;
            }

            for (int i = 0; i < 8; ++i)
            {
                Vec2i neighborIndex = {m_current.index.x + NEIGHBOR_INDICES[i].x,
                                       m_current.index.y + NEIGHBOR_INDICES[i].y};

                if (!checkFunction(neighborIndex.x, neighborIndex.y))
                {
                    continue;
                }

                AStarNode &neighbor  = m_nodes[neighborIndex];
                float costToNeighbor = m_current.gCost + dist(m_current.index, neighborIndex);

                if (neighbor.state == AStarNode::State::Unvisited || costToNeighbor < neighbor.gCost)
                {
                    AStarNode next;
                    next.index       = neighborIndex;
                    next.parentIndex = m_current.index;
                    next.hasParent   = true;
                    next.state       = AStarNode::State::Open;
                    next.gCost       = costToNeighbor;
                    next.hCost       = dist(neighborIndex, {m_end.x, m_end.y});
                    next.calculateFCost();

                    m_nodes[neighborIndex] = next;
                    m_toSearch.push(next);
                }
            }

            ++localIterations;
            ++m_iterationCount;
        }
    }
    std::vector<Vec2i> generatePath();

    bool pathFound() const { return m_pathFound; }
    void setConfig(Config config) { m_config = config; }

    Vec2i getStart() const { return m_start; }
    Vec2i getEnd() const { return m_end; }

  private:
    float dist(Vec2i start, Vec2i end);

  private:
    Config m_config;

    std::unordered_map<Vec2i, AStarNode, Vec2Hash<int>> m_nodes;
    std::priority_queue<AStarNode, std::vector<AStarNode>, AStarNodeCompare> m_toSearch;

    AStarNode m_current;

    Vec2i m_start, m_end;

    int m_iterationCount = 0;
    bool m_pathFound     = false;
};
