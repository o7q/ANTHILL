#pragma once

#include "core/math/geometry/vec.hpp"
#include <unordered_map>
#include <unordered_set>

template <typename T> struct Node
{
    Vec2i pos;
    T value{};
    std::unordered_set<Vec2i, Vec2Hash<int>> connections;
};

template <typename T> class NodeGraph
{
  public:
    void add(Vec2i index, Node<T> node) { m_nodes[index] = node; }

    const Node<T> *get(Vec2i index)
    {
        auto it = m_nodes.find(index);
        return it != m_nodes.end() ? &it->second : nullptr;
    }

    void connect(Vec2i a, Vec2i b)
    {
        m_nodes[a].connections.insert(b);
        m_nodes[b].connections.insert(a);
    }

    void clear() { m_nodes.clear(); }

    const std::unordered_map<Vec2i, Node<T>, Vec2Hash<int>> &getNodes() const { return m_nodes; }

  private:
    std::unordered_map<Vec2i, Node<T>, Vec2Hash<int>> m_nodes;
};
