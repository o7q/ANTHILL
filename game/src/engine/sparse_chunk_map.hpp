#pragma once

#include "utils.hpp"
#include <array>
#include <cstddef>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <utility>

template <typename T, std::size_t W, std::size_t H> class SparseChunkMap
{
    class Chunk
    {
      public:
        void set(unsigned int x, unsigned int y, T v)
        {
            m_values[Utils::index_2dto1d(x, y, W)] = v;
        }

        T get(int x, int y) { return m_values[Utils::index_2dto1d(x, y, W)]; }

      private:
        std::array<T, W * H> m_values;
    };

  public:
    void set(int x, int y, T v)
    {
        // safe casts
        int sx = static_cast<int>(x);
        int sW = static_cast<int>(W);
        int sy = static_cast<int>(y);
        int sH = static_cast<int>(H);

        int chunk_x;

        if (sx < 0)
        {
            
        }

        std::pair<int, int> index = std::pair<int, int>(x, y);
        // if (!m_chunks.contains(index))
        // {
        //     m_chunks.try_emplace(index, Chunk());
        //     return;
        // }

        // Chunk &chunk = m_chunks.at(index);

        int inner_x = sx % sW;

        std::cout << chunk_x << " : " << inner_x << std::endl;
        // chunk.set(value_x, value_y, v);
    }

    T get(int x, int y)
    {
        int chunk_x = x / W;
        int chunk_y = y / H;

        std::pair<int, int> index = std::pair<int, int>(x, y);
        if (!m_chunks.contains(index))
        {
            return T();
        }

        Chunk &chunk = m_chunks.at(index);

        unsigned int value_x = x % W;
        unsigned int value_y = y % H;
        return chunk.get(value_x, value_y);
    }

  private:
    std::unordered_map<std::pair<int, int>, Chunk, Utils::PairHash> m_chunks;
};
