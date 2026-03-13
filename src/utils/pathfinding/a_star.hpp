#pragma once

#include "backend/utils/vec.hpp"
#include "utils/data_structures/index_2d.hpp"
#include <cstdlib>
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

    void iteratePath(int amount);
    std::vector<Vec2<int>> generatePath();

    bool endReached() const { return m_endReached; }
    void setMaxIterations(int maxIterations)
    {
        m_maxIterations = maxIterations;
    }

  protected:
    virtual bool isNeighborWalkable(int x, int y) { return true; }

  private:
    float dist(Index2D start, Index2D end);

  private:
    std::priority_queue<AStarNode, std::vector<AStarNode>, AStarNodeCompare>
        m_toSearch;
    std::unordered_map<Index2D, AStarNode, Index2DHash> m_nodes;
    static constexpr int M_NEIGHBOR_INDICIES_X[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    static constexpr int M_NEIGHBOR_INDICIES_Y[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

    AStarNode m_current;

    Vec2<int> m_start, m_end;

    int m_maxIterations = 50000;
    int m_iterations = 0;

    bool m_endReached = false;
};
