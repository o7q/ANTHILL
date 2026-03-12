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
    std::unordered_map<Index2D, AStarNode, Index2DHash> nodes;

    AStarNode startNode;
    startNode.index = Index2D(start.x, start.y);
    startNode.hCost = dist({start.x, start.y}, {end.x, end.y});
    startNode.calculateFCost();
    startNode.state = State::Open;

    static constexpr int nx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    static constexpr int ny[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

    nodes[startNode.index] = startNode;
    toSearch.push(startNode);

    int iterations = 0;
    while (!toSearch.empty())
    {
        if (iterations > m_maxIterations)
        {
            return std::vector<Vec2<int>>();
        }

        AStarNode current = toSearch.top();
        toSearch.pop();

        if (nodes[current.index].state == State::Closed)
        {
            continue;
        }

        nodes[current.index].state = State::Closed;

        if (current.index == Index2D(end.x, end.y))
        {
            std::vector<Vec2<int>> path;
            AStarNode *node = &nodes[current.index];
            while (node->hasParent)
            {
                path.push_back({node->index.x, node->index.y});
                node = &nodes[node->parentIndex];
            }
            path.push_back({node->index.x, node->index.y});
            std::reverse(path.begin(), path.end());

            return path;
        }

        for (int i = 0; i < 8; ++i)
        {
            Index2D neighborIndex = {current.index.x + nx[i],
                                     current.index.y + ny[i]};

            if (!isNeighborWalkable(neighborIndex.x, neighborIndex.y))
            {
                continue;
            }

            AStarNode &neighbor = nodes[neighborIndex];
            float costToNeightbor =
                current.gCost + dist(current.index, neighborIndex);

            if (neighbor.state == State::Unvisited ||
                costToNeightbor < neighbor.gCost)
            {
                AStarNode next;
                next.index = neighborIndex;
                next.parentIndex = current.index;
                next.hasParent = true;
                next.state = State::Open;
                next.gCost = costToNeightbor;
                next.hCost = dist(neighborIndex, {end.x, end.y});
                next.calculateFCost();

                nodes[neighborIndex] = next;
                toSearch.push(next);
            }
        }

        ++iterations;
    }

    return std::vector<Vec2<int>>();
}

// https://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html#diagonal-distance
float AStarSolver::dist(Index2D start, Index2D end)
{
    int dx = std::abs(end.x - start.x);
    int dy = std::abs(end.y - start.y);
    // float D = 1.0f;
    // float D2 = 1.4142f; // sqrt(2)
    // return D * (dx + dy) + (D2 - 2.0f * D) * std::min(dx, dy);
    return (dx + dy);
}
