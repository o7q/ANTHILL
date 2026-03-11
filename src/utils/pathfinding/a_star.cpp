#include "a_star.hpp"

#include "backend/utils/vec.hpp"
#include "utils/data_structures/index_2d.hpp"
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <vector>

std::vector<Vec2<int>> AStarSolver::findPath(Vec2<int> start, Vec2<int> end)
{
    std::priority_queue<AStarNode, std::vector<AStarNode>, AStarNodeCompare>
        toSearch;

    std::unordered_map<Index2D, AStarNode, Index2DHash> open;
    std::unordered_map<Index2D, AStarNode, Index2DHash> closed;

    AStarNode startNode;
    startNode.hCost = dist({start.x, start.y}, {end.x, end.y});
    startNode.calculateFCost();
    startNode.index = Index2D(start.x, start.y);

    toSearch.push(startNode);
    open[startNode.index] = startNode;

    int iterations = 0;
    while (!toSearch.empty())
    {
        if (iterations > m_maxIterations)
        {
            return std::vector<Vec2<int>>();
        }

        AStarNode current = toSearch.top();
        toSearch.pop();
        open.erase(current.index);

        if (closed.count(current.index))
        {
            continue;
        }

        closed[current.index] = current;

        if (current.index == Index2D(end.x, end.y))
        {
            std::vector<Vec2<int>> path;
            AStarNode *node = &closed[current.index];
            while (node->hasParent)
            {
                path.push_back({node->index.x, node->index.y});
                node = &closed[node->parentIndex];
            }
            path.push_back({node->index.x, node->index.y});
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (Index2D neighborIndex : get_neighbors(current.index))
        {
            if (closed.count(neighborIndex))
            {
                continue;
            }

            float costToNeightbor =
                current.gCost + dist(current.index, neighborIndex);

            if (!open.count(neighborIndex) ||
                costToNeightbor < open[neighborIndex].gCost)
            {
                AStarNode next;
                next.index = neighborIndex;
                next.gCost = costToNeightbor;
                next.hCost = dist(neighborIndex, {end.x, end.y});
                next.calculateFCost();
                next.parentIndex = current.index;
                next.hasParent = true;

                toSearch.push(next);
                open[neighborIndex] = next;
            }
        }

        ++iterations;
    }

    return std::vector<Vec2<int>>();
}

// manhattan distance
float AStarSolver::dist(Index2D start, Index2D end)
{
    int dx = std::abs(end.x - start.x);
    int dy = std::abs(end.y - start.y);
    float D = 1.0f;
    return D * (dx + dy);
}

std::vector<Index2D> AStarSolver::get_neighbors(Index2D index)
{
    std::vector<Index2D> neighbors;
    for (int y = index.y - 1; y <= index.y + 1; ++y)
    {
        for (int x = index.x - 1; x <= index.x + 1; ++x)
        {
            if (x == index.x && y == index.y)
            {
                continue;
            }

            if (isNeighborWalkable(x, y))
            {
                neighbors.push_back({x, y});
            }
        }
    }
    return neighbors;
}
