#pragma once

#include "backend/utils/index.hpp"
#include "backend/utils/vec.hpp"
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
            m_values[Backend::Utils::Index::index_2dto1d(x, y, width)] = v;
        }

        const T *get(unsigned int x, unsigned int y, unsigned int width) const
        {
            return &m_values[Backend::Utils::Index::index_2dto1d(x, y, width)];
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
        m_chunkSize = Vec2<unsigned int>(chunkWidth, chunkHeight);
    }
    ChunkMap(const ChunkMap &other) = delete;
    ChunkMap &operator=(const ChunkMap &other) = delete;

    void set(int x, int y, T v)
    {
        Vec2<int> chunk_index = get_chunk_index(x, y);
        Index2D chunk_key(chunk_index.x, chunk_index.y);

        auto [it, _] =
            m_chunks.try_emplace(chunk_key, m_chunkSize.x, m_chunkSize.y);

        Vec2<unsigned int> inner_index = get_inner_index(x, y, chunk_index);
        it->second.set(inner_index.x, inner_index.y, v, m_chunkSize.x);
    }

    const T *get(int x, int y) const
    {
        Vec2<int> chunk_index = get_chunk_index(x, y);
        Index2D chunk_key(chunk_index.x, chunk_index.y);

        auto it = m_chunks.find(chunk_key);
        if (it == m_chunks.end())
        {
            return nullptr;
        }

        Vec2<unsigned int> inner_index = get_inner_index(x, y, chunk_index);
        return it->second.get(inner_index.x, inner_index.y, m_chunkSize.x);
    }

    T *get(int x, int y)
    {
        const T *v = static_cast<const ChunkMap *>(this)->get(x, y);
        return const_cast<T *>(v);
    }

    bool hasValue(int x, int y)
    {
        Vec2<int> chunk_index = get_chunk_index(x, y);
        Index2D chunk_key(chunk_index.x, chunk_index.y);

        auto it = m_chunks.find(chunk_key);
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

    Vec2<unsigned int> getChunkSize() const { return m_chunkSize; }

  private:
    Vec2<int> get_chunk_index(int x, int y) const
    {
        int cw = static_cast<int>(m_chunkSize.x);
        int ch = static_cast<int>(m_chunkSize.y);

        int chunk_x = x / cw - (x % cw < 0);
        int chunk_y = y / ch - (y % ch < 0);
        return Vec2<int>(chunk_x, chunk_y);
    }

    Vec2<unsigned int> get_inner_index(int x, int y,
                                       Vec2<int> chunk_index) const
    {
        int cw = static_cast<int>(m_chunkSize.x);
        int ch = static_cast<int>(m_chunkSize.y);

        unsigned int inner_x = x - chunk_index.x * cw;
        unsigned int inner_y = y - chunk_index.y * ch;
        return Vec2<unsigned int>(inner_x, inner_y);
    }

  private:
    Vec2<unsigned int> m_chunkSize;

    std::unordered_map<Index2D, Chunk, Index2DHash> m_chunks;
};
