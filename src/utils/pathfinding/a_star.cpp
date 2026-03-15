#include "a_star.hpp"

#include "backend/utils/vec.hpp"
#include "utils/data_structures/index_2d.hpp"
#include <algorithm>
#include <unordered_map>

// https://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html#diagonal-distance
float AStarSolver::dist(Index2D start, Index2D end)
{
    int dx = std::abs(end.x - start.x);
    int dy = std::abs(end.y - start.y);
    float D = 1.0f;
    float D2 = 1.4142f; // sqrt(2)
    return D * (dx + dy) + (D2 - 2.0f * D) * std::min(dx, dy);
}

std::vector<Vec2<int>> AStarSolver::generatePath()
{
    std::vector<Vec2<int>> path;
    AStarNode *node = &m_nodes[m_current.index];
    while (node->hasParent)
    {
        path.push_back({node->index.x, node->index.y});
        node = &m_nodes[node->parentIndex];
    }
    path.push_back({node->index.x, node->index.y});
    std::reverse(path.begin(), path.end());

    return path;
}

void AStarSolver::reset(Vec2<int> start, Vec2<int> end)
{
    m_nodes.clear();
    m_toSearch = std::priority_queue<AStarNode, std::vector<AStarNode>,
                                     AStarNodeCompare>();

    // m_current = {};

    m_start = start;
    m_end = end;

    m_endReached = false;

    m_iterations = 0;

    AStarNode startNode;
    startNode.index = Index2D(start.x, start.y);
    startNode.hCost = dist({start.x, start.y}, {end.x, end.y});
    startNode.calculateFCost();
    startNode.state = State::Open;

    m_nodes[startNode.index] = startNode;
    m_toSearch.push(startNode);
}
