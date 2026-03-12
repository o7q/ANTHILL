#pragma once

#include "backend/utils/vec.hpp"
#include "utils/data_structures/index_2d.hpp"
#include <algorithm>
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
    AStarSolver() = default;
    virtual ~AStarSolver() = default;

    void reset(Vec2<int> start, Vec2<int> end)
    {
        m_nodes.clear();
        m_toSearch = std::priority_queue<AStarNode, std::vector<AStarNode>,
                                         AStarNodeCompare>();

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

    void iteratePath(int amount);

    std::vector<Vec2<int>> generatePath()
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

    bool endReached() const { return m_endReached; }

    void setMaxIterations(int maxIterations)
    {
        m_maxIterations = maxIterations;
    }

  protected:
    virtual bool isNeighborWalkable(int x, int y) { return true; }

  private:
    float dist(Index2D start, Index2D end);
    std::vector<Index2D> get_neighbors(Index2D index);

  private:
    std::priority_queue<AStarNode, std::vector<AStarNode>, AStarNodeCompare>
        m_toSearch;
    std::unordered_map<Index2D, AStarNode, Index2DHash> m_nodes;

    AStarNode m_current;

    static constexpr int m_neighborX[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    static constexpr int m_neighborY[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

    Vec2<int> m_start, m_end;

    int m_maxIterations = 50000;
    int m_iterations = 0;

    bool m_endReached = false;
};
