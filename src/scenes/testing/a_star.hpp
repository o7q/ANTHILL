#pragma once

#include "backend/types/vec.hpp"
#include "types/data_structures/chunk_map.hpp"
#include "world/particle/particle.hpp"
#include <vector>

struct AStarNode
{
    Vec2<int> position;
    int parentIndex = -1;

    float gCost = 0.0f; // distance from starting node
    float hCost = 0.0f; // distance from end node
    float fCost() const { return gCost + hCost; }
};

inline float dist(Vec2<int> start, Vec2<int> end)
{
    return (start - end).toFloat().length();
}

inline std::vector<Vec2<int>> getNeighbors(Vec2<int> pos,
                                           ChunkMap<Particle> &particles)
{
    std::vector<Vec2<int>> neighbors;

    for (int y = pos.y - 1; y <= pos.y + 1; ++y)
    {
        for (int x = pos.x - 1; x <= pos.x + 1; ++x)
        {
            if (x == pos.x && y == pos.y)
            {
                continue;
            }

            if (Particle *p = particles.get(x, y))
            {
                if (!p->isSolid() || p->isMoving())
                {
                    neighbors.push_back({x, y});
                }
            }
            else
            {
                neighbors.push_back({x, y});
            }
        }
    }

    return neighbors;
}

inline std::vector<Vec2<int>> findPath(Vec2<int> start, Vec2<int> end,
                                       ChunkMap<Particle> &particles)
{
    std::vector<AStarNode> toSearch;
    std::vector<AStarNode> processed;

    AStarNode startNode;
    startNode.hCost = dist(start, end);
    startNode.position = start;
    toSearch.push_back(startNode);

    while (toSearch.size() > 0)
    {
        int bestIndex = 0;

        for (int i = 0; i < static_cast<int>(toSearch.size()); ++i)
        {
            if (toSearch[i].fCost() < toSearch[bestIndex].fCost() ||
                (toSearch[i].fCost() == toSearch[bestIndex].fCost() &&
                 toSearch[i].hCost < toSearch[bestIndex].hCost))
            {
                bestIndex = i;
            }
        }

        AStarNode current = toSearch[bestIndex];
        toSearch.erase(toSearch.begin() + bestIndex);

        int currentProcessedIndex = static_cast<int>(processed.size());
        processed.push_back(current);

        if (current.position == end)
        {
            std::vector<Vec2<int>> path;

            int index = currentProcessedIndex;

            while (index != -1)
            {
                path.push_back(processed[index].position);
                index = processed[index].parentIndex;
            }

            return path;
        }

        for (Vec2<int> neighborPos : getNeighbors(current.position, particles))
        {
            bool alreadyProcessed = false;

            for (auto &p : processed)
            {
                if (p.position == neighborPos)
                {
                    alreadyProcessed = true;
                    break;
                }
            }
            if (alreadyProcessed)
            {
                continue;
            }

            float costToNeightbor =
                current.gCost + dist(current.position, neighborPos);

            bool foundBetter = false;
            for (auto &node : toSearch)
            {
                if (node.position == neighborPos)
                {
                    if (costToNeightbor < node.gCost)
                    {
                        node.gCost = costToNeightbor;
                    }
                    foundBetter = true;
                    break;
                }
            }

            if (!foundBetter)
            {
                AStarNode test;
                test.position = neighborPos;
                test.gCost = costToNeightbor;
                test.hCost = dist(neighborPos, end);
                test.parentIndex = currentProcessedIndex;
                toSearch.push_back(test);
            }
        }
    }

    return std::vector<Vec2<int>>();
}
