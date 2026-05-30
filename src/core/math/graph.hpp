#pragma once

#include "core/data_structures/node_graph.hpp"
#include "core/math/geometry/triangle.hpp"
#include "core/math/geometry/vec.hpp"
#include <limits>
#include <unordered_set>

namespace Math
{
namespace Graph
{
template <typename T>
inline NodeGraph<T> connectNodesFromTriangulation(const std::vector<Triangle_i> &triangulation,
                                                  const NodeGraph<T> &input)
{
    NodeGraph<T> out = input;
    for (Triangle_i tri : triangulation)
    {
        out.connect(tri.verts[0], tri.verts[1]);
        out.connect(tri.verts[1], tri.verts[2]);
        out.connect(tri.verts[2], tri.verts[0]);
    }
    return out;
}

// prim's algorithm
// https://www.youtube.com/watch?v=cplfcGZmX7I
template <typename T> inline NodeGraph<T> minimumSpanningTree(const NodeGraph<T> &input)
{
    NodeGraph<T> tree = input;
    tree.clearConnections();

    std::unordered_set<Vec2i, Vec2Hash<int>> visited;
    visited.insert(input.getNodes().begin()->first);

    while (visited.size() < input.getNodes().size())
    {
        Vec2i bestStart, bestConnection;
        float smallestDist   = std::numeric_limits<float>::max();
        bool foundConnection = false;
        for (Vec2i visitedIndex : visited)
        {
            const Node<T> *neighbor = input.get(visitedIndex);
            for (Vec2i neighborIndex : neighbor->connections)
            {
                if (visited.find(neighborIndex) != visited.end())
                {
                    continue;
                }

                float dist = (visitedIndex - neighborIndex).length();

                if (dist < smallestDist)
                {
                    bestStart       = visitedIndex;
                    bestConnection  = neighborIndex;
                    smallestDist    = dist;
                    foundConnection = true;
                }
            }
        }

        if (!foundConnection)
        {
            break;
        }

        tree.connect(bestStart, bestConnection);
        visited.insert(bestConnection);
    }

    return tree;
}
} // namespace Graph
} // namespace Math
