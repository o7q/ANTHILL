#pragma once

#include "core/logger/logger.hpp"
#include "core/math/geometry/segment.hpp"
#include "core/math/geometry/vec.hpp"
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T> struct Node
{
    T value{};
    std::unordered_set<Vec2i, Vec2Hash<int>> connections;
};

template <typename T> class NodeGraph
{
  public:
    void set(Vec2i index, Node<T> node) { m_nodes[index] = node; }
    void remove(Vec2i index) { m_nodes.erase(index); }

    const Node<T> *get(Vec2i index) const
    {
        auto it = m_nodes.find(index);
        return it != m_nodes.end() ? &it->second : nullptr;
    }

    void move(Vec2i index, Vec2i newIndex)
    {
        if (m_nodes.find(index) == m_nodes.end())
        {
            Logger::error("NodeGraph::move()", "Invalid move attempt at: (" + std::to_string(index.x) + ", " +
                                                   std::to_string(index.y) + ") to (" +
                                                   std::to_string(newIndex.x) + ", " +
                                                   std::to_string(newIndex.y) + ")");
            return;
        }

        m_nodes[newIndex] = m_nodes.at(index);
        m_nodes.erase(index);
    }

    void connect(Vec2i a, Vec2i b)
    {
        if (m_nodes.find(a) == m_nodes.end() || m_nodes.find(b) == m_nodes.end() || a == b)
        {
            Logger::error("NodeGraph::connect()", "Invalid connection attempt at: (" + std::to_string(a.x) +
                                                      ", " + std::to_string(a.y) + ") (" +
                                                      std::to_string(b.x) + ", " + std::to_string(b.y) + ")");
            return;
        }

        m_nodes.at(a).connections.insert(b);
        m_nodes.at(b).connections.insert(a);
    }

    void clear() { m_nodes.clear(); }
    void clearConnections()
    {
        for (auto &[index, node] : m_nodes)
        {
            node.connections.clear();
        }
    }

    void merge(const NodeGraph<T> &other)
    {
        for (auto &[index, node] : other.getNodes())
        {
            set(index, node);
        }
    }

    std::vector<Vec2i> generatePositions() const
    {
        std::vector<Vec2i> out;
        out.reserve(m_nodes.size());
        for (auto &[index, _] : m_nodes)
        {
            out.push_back(index);
        }
        return out;
    }

    std::unordered_set<Segment_i, SegmentHash<int>> generateConnections() const
    {
        auto normalize = [&](Vec2i a, Vec2i b) { return a < b ? Segment_i{a, b} : Segment_i{b, a}; };

        std::unordered_set<Segment_i, SegmentHash<int>> out;

        for (auto &[index, node] : m_nodes)
        {
            for (Vec2i connection : node.connections)
            {
                out.insert(normalize(index, connection));
            }
        }

        return out;
    }

    void reserve(size_t size) { m_nodes.reserve(size); }

    const std::unordered_map<Vec2i, Node<T>, Vec2Hash<int>> &getNodes() const { return m_nodes; }

  private:
    std::unordered_map<Vec2i, Node<T>, Vec2Hash<int>> m_nodes;
};
