#pragma once

#include "math/vec.hpp"
#include "utils/data_structures/index_2d.hpp"
#include <cstdlib>
#include <optional>
#include <queue>
#include <vector>

class AStarSolver
{
  private:
    enum class State
    {
        Open,
        Closed,
        Unvisited
    };

    struct AStarNode
    {
        Index2D index;
        Index2D parentIndex;
        bool hasParent = false;

        State state = State::Unvisited;

        float gCost = 0.0f; // distance from starting node
        float hCost = 0.0f; // distance from end node
        float fCostCached = 0.0f;
        void calculateFCost() { fCostCached = gCost + hCost; }
    };

    struct AStarNodeCompare
    {
        bool operator()(const AStarNode &a, const AStarNode &b) const
        {
            if (std::abs(a.fCostCached - b.fCostCached) > 0.000001f)
            {
                return a.fCostCached > b.fCostCached;
            }

            return a.hCost > b.hCost;
        }
    };

  public:
    AStarSolver() { reset(Vec2i(0, 0), Vec2i(0, 0)); }
    virtual ~AStarSolver() = default;

    void reset(Vec2i start, Vec2i end);

    template <typename NeighborCheckFunction>
    void iteratePath(int amount, NeighborCheckFunction &&checkFunction)
    {
        int localIterations = 0;
        while (!m_toSearch.empty() && localIterations < amount && !m_endReached)
        {
            if (m_iterationCount > m_maxIterations)
            {
                return;
            }

            m_current = m_toSearch.top();
            m_toSearch.pop();

            if (m_nodes[m_current.index].state == State::Closed)
            {
                continue;
            }

            m_nodes[m_current.index].state = State::Closed;

            bool terminate = false;

            if (m_terminateDistance.has_value())
            {
                int terminateDistTest = std::abs(m_current.index.x - m_end.x) +
                                        std::abs(m_current.index.y - m_end.y);

                if (terminateDistTest < m_terminateDistance)
                {
                    terminate = true;
                }
            }

            if (m_current.index == Index2D(m_end.x, m_end.y) || terminate)
            {
                m_endReached = true;
                return;
            }

            for (int i = 0; i < 8; ++i)
            {
                Index2D neighborIndex = {
                    m_current.index.x + M_NEIGHBOR_INDICIES_X[i],
                    m_current.index.y + M_NEIGHBOR_INDICIES_Y[i]};

                if (!checkFunction(neighborIndex.x, neighborIndex.y))
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

            ++localIterations;
            ++m_iterationCount;
        }
    }
    std::vector<Vec2i> generatePath();

    bool endReached() const { return m_endReached; }
    void setMaxIterations(int maxIterations)
    {
        m_maxIterations = maxIterations;
    }

    void setTerminateDistance(int distance) { m_terminateDistance = distance; }
    void removeTerminateDistance() { m_terminateDistance = std::nullopt; }

    Vec2i getStart() const { return m_start; }
    Vec2i getEnd() const { return m_end; }

  private:
    float dist(Index2D start, Index2D end);

  private:
    static constexpr int M_NEIGHBOR_INDICIES_X[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    static constexpr int M_NEIGHBOR_INDICIES_Y[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

    std::unordered_map<Index2D, AStarNode, Index2DHash> m_nodes;
    std::priority_queue<AStarNode, std::vector<AStarNode>, AStarNodeCompare>
        m_toSearch;

    AStarNode m_current;

    Vec2i m_start, m_end;

    int m_maxIterations = 50000;
    int m_iterationCount = 0;

    bool m_endReached = false;

    std::optional<int> m_terminateDistance = 0;
};
