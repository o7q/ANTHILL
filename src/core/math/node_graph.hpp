#pragma once

#include "core/math/geometry/triangle.hpp"
#include <cstdint>
#include <unordered_map>
#include <vector>

template <typename T> class Node
{
  public:
    void setValue(T value) { m_value = value; }
    const T &getValue() const { return m_value; }
    void setConnections(const std::vector<uint64_t> &connections) { m_connections = connections; }
    const std::vector<uint64_t> &getConnections() const { return m_connections; }

  private:
    T m_value{};
    std::vector<uint64_t> m_connections;
};

template <typename T> class NodeGraph
{
    std::unordered_map<uint64_t, Node<T>> m_nodes;
};

template <typename T> inline NodeGraph<T> graphFromTriangulation(const std::vector<Triangle2i> &triangulation)
{
    NodeGraph<T> graph;
}
