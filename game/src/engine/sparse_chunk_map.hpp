#pragma once

#include "logger.hpp"
#include "utils.hpp"
#include <array>
#include <cstddef>
#include <unordered_map>
#include <utility>

template <typename T, std::size_t W, std::size_t H> class SparseChunkMap
{
  public:
    class Chunk
    {
      public:
        void set(unsigned int x, unsigned int y, T v)
        {
            m_values[Utils::index_2dto1d(x, y, W)] = v;
        }

        T get(int x, int y) { return m_values[Utils::index_2dto1d(x, y, W)]; }

      private:
        std::array<T, W * H> m_values{};
    };

  public:
    SparseChunkMap() : m_logger("SparseChunkMap") {}
    SparseChunkMap(const SparseChunkMap &other) = delete;
    SparseChunkMap &operator=(const SparseChunkMap &other) = delete;

    void set(int x, int y, T v)
    {
        Vec2<int> chunk_index = get_chunk_index(x, y);
        std::pair<int, int> chunk_key(chunk_index.x, chunk_index.y);

        auto [it, inserted] = m_chunks.try_emplace(chunk_key);
        if (inserted)
        {
            m_logger.log(Logger::Severity::Info, "set",
                         "Chunk at: (" + std::to_string(chunk_index.x) + " " +
                             std::to_string(chunk_index.y) +
                             ") didn't exist, created an empty chunk");
        }

        Vec2<unsigned int> inner_index = get_inner_index(x, y, chunk_index);
        m_chunks[chunk_key].set(inner_index.x, inner_index.y, v);
    }

    T get(int x, int y)
    {
        Vec2<int> chunk_index = get_chunk_index(x, y);
        std::pair<int, int> chunk_key(chunk_index.x, chunk_index.y);

        if (!m_chunks.contains(chunk_key))
        {
            return T();
        }

        Vec2<unsigned int> inner_index = get_inner_index(x, y, chunk_index);
        return m_chunks[chunk_key].get(inner_index.x, inner_index.y);
    }

    const std::unordered_map<std::pair<int, int>, Chunk, Utils::PairHash> &
    getChunks() const
    {
        return m_chunks;
    }

    Vec2<unsigned int> getSize() const
    {
        return Vec2<unsigned int>(m_iW, m_iH);
    }

  private:
    Vec2<int> get_chunk_index(int x, int y)
    {
        int chunk_x = x / m_iW - (x % m_iW < 0);
        int chunk_y = y / m_iH - (y % m_iH < 0);
        return Vec2<int>(chunk_x, chunk_y);
    }

    Vec2<unsigned int> get_inner_index(int x, int y, Vec2<int> chunk_index)
    {
        unsigned int inner_x = x - chunk_index.x * m_iW;
        unsigned int inner_y = y - chunk_index.y * m_iH;
        return Vec2<unsigned int>(inner_x, inner_y);
    }

  private:
    const int m_iW = static_cast<int>(W);
    const int m_iH = static_cast<int>(H);

    std::unordered_map<std::pair<int, int>, Chunk, Utils::PairHash> m_chunks;
    Logger m_logger;
};
