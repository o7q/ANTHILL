#include "a_star.hpp"

#include "core/math/geometry/vec.hpp"
#include <algorithm>
#include <unordered_map>

// https://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html#diagonal-distance
float AStarSolver::dist(Vec2i start, Vec2i end)
{
    int dx   = std::abs(end.x - start.x);
    int dy   = std::abs(end.y - start.y);
    float D  = 1.0f;
    float D2 = 1.4142f; // sqrt(2)
    return D * (dx + dy) + (D2 - 2.0f * D) * std::min(dx, dy);
}

std::vector<Vec2i> AStarSolver::generatePath()
{
    std::vector<Vec2i> path;
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

void AStarSolver::reset(Vec2i start, Vec2i end)
{
    m_nodes.clear();
    m_toSearch = std::priority_queue<AStarNode, std::vector<AStarNode>, AStarNodeCompare>();

    m_current = AStarNode();

    m_start = start;
    m_end   = end;

    m_pathFound = false;

    m_iterationCount = 0;

    AStarNode startNode;
    startNode.index = start;
    startNode.hCost = dist({start.x, start.y}, {end.x, end.y});
    startNode.calculateFCost();
    startNode.state = AStarNode::State::Open;

    m_nodes[startNode.index] = startNode;
    m_toSearch.push(startNode);
}
