#pragma once

#include "backend/types/vec.hpp"
#include "types/data_structures/index_2d.hpp"
#include <cstdlib>
#include <vector>

class AStarSystem
{
  private:
    struct AStarNode
    {
        Index2D index;
        Index2D parentIndex;
        bool hasParent = false;

        float gCost = 0.0f; // distance from starting node
        float hCost = 0.0f; // distance from end node
        float fCostCached = 0.0f;
        void calculateFCost() { fCostCached = gCost + hCost; }
    };

    struct AStarNodeCompare
    {
        bool operator()(const AStarNode &a, const AStarNode &b) const
        {
            if (std::abs(a.fCostCached - b.fCostCached) > 0.0001f)
            {
                return a.fCostCached > b.fCostCached;
            }

            return a.hCost > b.hCost;
        }
    };

  public:
    AStarSystem() = default;
    virtual ~AStarSystem() = default;

    std::vector<Vec2<int>> findPath(Vec2<int> start, Vec2<int> end);

    void setMaxIterations(int maxIterations)
    {
        m_maxIterations = maxIterations;
    }

  protected:
    virtual bool isNeighborWalkable(int x, int y) { return true; }

  private:
    float dist(Index2D start, Index2D end);
    std::vector<Index2D> get_neighbors(Index2D index);

    int m_maxIterations = 50000;
};
