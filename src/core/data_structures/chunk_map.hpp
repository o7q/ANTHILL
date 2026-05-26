#pragma once

#include "core/math/geometry/vec.hpp"
#include "core/math/index.hpp"
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
        Vec2i chunk_index = getChunkIndex(pos);

        auto [it, _] = m_chunks.try_emplace(chunk_index, m_chunkSize);

        Vec2u inner_index = getInnerIndex(pos, chunk_index);
        it->second.set(inner_index, value, m_chunkSize.x);
    }

    const T *get(Vec2i globalPos) const
    {
        Vec2i chunk_index = getChunkIndex(globalPos);

        auto it = m_chunks.find(chunk_index);
        if (it == m_chunks.end())
        {
            return nullptr;
        }

        Vec2u inner_index = getInnerIndex(globalPos, chunk_index);
        return it->second.get(inner_index, m_chunkSize.x);
    }

    T *get(Vec2i globalPos)
    {
        const T *v = static_cast<const ChunkMap *>(this)->get(globalPos);
        return const_cast<T *>(v);
    }

    bool hasChunk(Vec2i chunkPos) const
    {
        auto it = m_chunks.find(chunkPos);
        return it != m_chunks.end();
    }

    bool hasChunkAtPosition(Vec2i globalPos)
    {
        Vec2i chunk_index = getChunkIndex(globalPos);

        auto it = m_chunks.find(chunk_index);
        return it != m_chunks.end();
    }

    void swap(Vec2i globalPos1, Vec2i globalPos2)
    {
        T *a = get(globalPos1);
        T *b = get(globalPos2);

        if (!a || !b)
        {
            return;
        }

        std::swap(*a, *b);
    }

    void move(Vec2i globalPos1, Vec2i globalPos2)
    {
        T *a = get(globalPos1);
        if (!a)
        {
            return;
        }
        T v = *a;
        set(globalPos1, T{});
        set(globalPos2, v);
    }

    const std::unordered_map<Vec2i, Chunk, Vec2Hash<int>> &getChunks() const { return m_chunks; }

    Vec2u getChunkSize() const { return m_chunkSize; }

    Vec2i getChunkIndex(Vec2i globalPos) const
    {
        return (globalPos.toFloat() / m_chunkSize.toFloat()).toGrid();
    }

    Vec2u getInnerIndex(Vec2i globalPos, Vec2i chunkPos) const
    {
        int cw = static_cast<int>(m_chunkSize.x);
        int ch = static_cast<int>(m_chunkSize.y);

        unsigned int inner_x = globalPos.x - chunkPos.x * cw;
        unsigned int inner_y = globalPos.y - chunkPos.y * ch;
        return Vec2u(inner_x, inner_y);
    }

    void erase(Vec2i chunkPos) { m_chunks.erase(chunkPos); }

  private:
    Vec2u m_chunkSize;
    std::unordered_map<Vec2i, Chunk, Vec2Hash<int>> m_chunks;
};
