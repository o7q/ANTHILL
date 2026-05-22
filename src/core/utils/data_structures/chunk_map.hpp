#pragma once

#include "core/math/index.hpp"
#include "core/math/geometry/vec.hpp"
#include "core/utils/data_structures/index_2d.hpp"
#include <unordered_map>
#include <vector>

template <typename T> class ChunkMap
{
  public:
    class Chunk
    {
      public:
        Chunk(Vec2u size) { m_values.resize(size.x * size.y); }
        Chunk(const Chunk &other)            = delete;
        Chunk &operator=(const Chunk &other) = delete;

        void set(Vec2u pos, T value, unsigned int width)
        {
            m_values[Math::Index::index_2dto1d(pos, width)] = value;
        }

        const T *get(Vec2u pos, unsigned int width) const
        {
            return &m_values[Math::Index::index_2dto1d(pos, width)];
        }

        T *get(Vec2u pos, unsigned int width)
        {
            const T *v = static_cast<const Chunk *>(this)->get(pos, width);
            return const_cast<T *>(v);
        }

      private:
        std::vector<T> m_values;
    };

  public:
    ChunkMap(Vec2u chunkSize) { m_chunkSize = chunkSize; }
    ChunkMap(const ChunkMap &other)            = delete;
    ChunkMap &operator=(const ChunkMap &other) = delete;

    void set(Vec2i pos, T value)
    {
        Index2D chunk_index = getChunkIndex(pos);

        auto [it, _] = m_chunks.try_emplace(chunk_index, m_chunkSize);

        Vec2u inner_index = getInnerIndex(pos, chunk_index);
        it->second.set(inner_index, value, m_chunkSize.x);
    }

    const T *get(Vec2i pos) const
    {
        Index2D chunk_index = getChunkIndex(pos);

        auto it = m_chunks.find(chunk_index);
        if (it == m_chunks.end())
        {
            return nullptr;
        }

        Vec2u inner_index = getInnerIndex(pos, chunk_index);
        return it->second.get(inner_index, m_chunkSize.x);
    }

    T *get(Vec2i pos)
    {
        const T *v = static_cast<const ChunkMap *>(this)->get(pos);
        return const_cast<T *>(v);
    }

    bool hasChunk(Index2D index) const
    {
        auto it = m_chunks.find(index);
        return it != m_chunks.end();
    }

    bool hasChunkAtPosition(Vec2i pos)
    {
        Index2D chunk_index = getChunkIndex(pos);

        auto it = m_chunks.find(chunk_index);
        return it != m_chunks.end();
    }

    void swap(Vec2i p1, Vec2i p2)
    {
        T *a = get(p1);
        T *b = get(p2);

        if (!a || !b)
        {
            return;
        }

        std::swap(*a, *b);
    }

    void move(Vec2i p1, Vec2i p2)
    {
        T *a = get(p1);
        if (!a)
        {
            return;
        }
        T v = *a;
        set(p1, T());
        set(p2, v);
    }

    const std::unordered_map<Index2D, Chunk, Index2DHash> &getChunks() const { return m_chunks; }

    Vec2u getChunkSize() const { return m_chunkSize; }

    Index2D getChunkIndex(Vec2i pos) const
    {
        int cw = static_cast<int>(m_chunkSize.x);
        int ch = static_cast<int>(m_chunkSize.y);

        int chunk_x = pos.x / cw - (pos.x % cw < 0);
        int chunk_y = pos.y / ch - (pos.y % ch < 0);
        return Index2D(chunk_x, chunk_y);
    }

    Vec2u getInnerIndex(Vec2i pos, Index2D index) const
    {
        int cw = static_cast<int>(m_chunkSize.x);
        int ch = static_cast<int>(m_chunkSize.y);

        unsigned int inner_x = pos.x - index.x * cw;
        unsigned int inner_y = pos.y - index.y * ch;
        return Vec2u(inner_x, inner_y);
    }

  private:
    Vec2u m_chunkSize;
    std::unordered_map<Index2D, Chunk, Index2DHash> m_chunks;
};
