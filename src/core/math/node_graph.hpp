#pragma once

#include "core/math/geometry/triangle.hpp"
#include "core/utils/data_structures/index_2d.hpp"
#include <unordered_map>
#include <vector>

template <typename T> class Node
{
  public:
    void setValue(T value) { m_value = value; }
    const T &getValue() const { return m_value; }
    void setConnections(const std::vector<Index2D> &connections) { m_connections = connections; }
    const std::vector<Index2D> &getConnections() const { return m_connections; }

  private:
    T m_value{};
    std::vector<Index2D> m_connections;
};

template <typename T> class NodeGraph
{
  public:
    void addNode(Index2D index, Node<T> node) { m_nodes[index] = node; }
    const std::unordered_map<Index2D, Node<T>, Index2DHash> &getNodes() const { return m_nodes; }

  private:
    std::unordered_map<Index2D, Node<T>, Index2DHash> m_nodes;
};

template <typename T> inline NodeGraph<T> graphFromTriangulation(const std::vector<Triangle_i> &triangulation)
{
    NodeGraph<T> graph;
}
