#pragma once

#include "backend/utils/vec.hpp"
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
    AStarSolver() { reset(Vec2<int>(0, 0), Vec2<int>(0, 0)); }
    virtual ~AStarSolver() = default;

    void reset(Vec2<int> start, Vec2<int> end);

    template <typename NeighborCheckFunction>
    void iteratePath(int amount, NeighborCheckFunction &&checkFunction)
    {
        int i = 0;
        while (!m_toSearch.empty() && i < amount && !m_endReached)
        {
            if (m_iterations > m_maxIterations)
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
                int distTest = std::abs(m_current.index.x - m_end.x) +
                               std::abs(m_current.index.y - m_end.y);

                if (distTest < m_terminateDistance)
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

            ++i;
            ++m_iterations;
        }
    }
    std::vector<Vec2<int>> generatePath();

    bool endReached() const { return m_endReached; }
    void setMaxIterations(int maxIterations)
    {
        m_maxIterations = maxIterations;
    }

    void setTerminateDistance(int distance) { m_terminateDistance = distance; }
    void removeTerminateDistance() { m_terminateDistance = std::nullopt; }

  private:
    float dist(Index2D start, Index2D end);

  private:
    std::unordered_map<Index2D, AStarNode, Index2DHash> m_nodes;
    std::priority_queue<AStarNode, std::vector<AStarNode>, AStarNodeCompare>
        m_toSearch;
    static constexpr int M_NEIGHBOR_INDICIES_X[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    static constexpr int M_NEIGHBOR_INDICIES_Y[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

    AStarNode m_current;

    Vec2<int> m_start, m_end;

    int m_maxIterations = 50000;
    int m_iterations = 0;

    bool m_endReached = false;

    std::optional<int> m_terminateDistance = 0;
};
