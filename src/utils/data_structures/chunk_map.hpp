#pragma once

#include "math/index.hpp"
#include "math/vec.hpp"
#include "utils/data_structures/index_2d.hpp"
#include <unordered_map>
#include <vector>

template <typename T> class ChunkMap
{
  public:
    class Chunk
    {
      public:
        Chunk(unsigned int width, unsigned int height)
        {
            m_values.resize(width * height);
        }
        Chunk(const Chunk &other) = delete;
        Chunk &operator=(const Chunk &other) = delete;

        void set(unsigned int x, unsigned int y, T v, unsigned int width)
        {
            m_values[Math::Index::index_2dto1d(x, y, width)] = v;
        }

        const T *get(unsigned int x, unsigned int y, unsigned int width) const
        {
            return &m_values[Math::Index::index_2dto1d(x, y, width)];
        }

        T *get(unsigned int x, unsigned int y, unsigned int width)
        {
            const T *v = static_cast<const Chunk *>(this)->get(x, y, width);
            return const_cast<T *>(v);
        }

      private:
        std::vector<T> m_values;
    };

  public:
    ChunkMap(unsigned int chunkWidth, unsigned int chunkHeight)
    {
        m_chunkSize = Vec2u(chunkWidth, chunkHeight);
    }
    ChunkMap(const ChunkMap &other) = delete;
    ChunkMap &operator=(const ChunkMap &other) = delete;

    void set(int x, int y, T v)
    {
        Index2D chunk_index = getChunkIndex(x, y);

        auto [it, _] =
            m_chunks.try_emplace(chunk_index, m_chunkSize.x, m_chunkSize.y);

        Vec2u inner_index = getInnerIndex(x, y, chunk_index);
        it->second.set(inner_index.x, inner_index.y, v, m_chunkSize.x);
    }

    const T *get(int x, int y) const
    {
        Index2D chunk_index = getChunkIndex(x, y);

        auto it = m_chunks.find(chunk_index);
        if (it == m_chunks.end())
        {
            return nullptr;
        }

        Vec2u inner_index = getInnerIndex(x, y, chunk_index);
        return it->second.get(inner_index.x, inner_index.y, m_chunkSize.x);
    }

    T *get(int x, int y)
    {
        const T *v = static_cast<const ChunkMap *>(this)->get(x, y);
        return const_cast<T *>(v);
    }

    bool hasChunk(Index2D index)
    {
        auto it = m_chunks.find(index);
        return it != m_chunks.end();
    }

    bool hasChunkAtPosition(int x, int y)
    {
        Index2D chunk_index = getChunkIndex(x, y);

        auto it = m_chunks.find(chunk_index);
        return it != m_chunks.end();
    }

    void swap(int x1, int y1, int x2, int y2)
    {
        T *a = get(x1, y1);
        T *b = get(x2, y2);

        if (!a || !b)
        {
            return;
        }

        std::swap(*a, *b);
    }

    void move(int x1, int y1, int x2, int y2)
    {
        T *a = get(x1, y1);
        if (!a)
        {
            return;
        }
        T v = *a;
        set(x1, y1, T());
        set(x2, y2, v);
    }

    const std::unordered_map<Index2D, Chunk, Index2DHash> &getChunks() const
    {
        return m_chunks;
    }

    Vec2u getChunkSize() const { return m_chunkSize; }

    Index2D getChunkIndex(int x, int y) const
    {
        int cw = static_cast<int>(m_chunkSize.x);
        int ch = static_cast<int>(m_chunkSize.y);

        int chunk_x = x / cw - (x % cw < 0);
        int chunk_y = y / ch - (y % ch < 0);
        return Index2D(chunk_x, chunk_y);
    }

    Vec2u getInnerIndex(int x, int y, Index2D index) const
    {
        int cw = static_cast<int>(m_chunkSize.x);
        int ch = static_cast<int>(m_chunkSize.y);

        unsigned int inner_x = x - index.x * cw;
        unsigned int inner_y = y - index.y * ch;
        return Vec2u(inner_x, inner_y);
    }

  private:
    Vec2u m_chunkSize;
    std::unordered_map<Index2D, Chunk, Index2DHash> m_chunks;
};
