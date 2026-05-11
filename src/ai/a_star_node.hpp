#pragma once

#include "core/utils/data_structures/index_2d.hpp"
#include <cstdlib>

struct AStarNode
{
    enum class State
    {
        Open,
        Closed,
        Unvisited
    };

    Index2D index;
    Index2D parentIndex;
    bool hasParent = false;

    State state = State::Unvisited;

    float gCost       = 0.0f; // distance from starting node
    float hCost       = 0.0f; // distance from end node
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
