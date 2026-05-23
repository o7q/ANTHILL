#pragma once

#include "core/math/geometry/vec.hpp"
#include <cmath>

struct AStarNode
{
    enum class State
    {
        Open,
        Closed,
        Unvisited
    };

    Vec2i index;
    Vec2i parentIndex;
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
