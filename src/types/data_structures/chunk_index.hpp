#pragma once

#include <functional>

struct ChunkIndex
{
    int x = 0, y = 0;

    ChunkIndex(int x, int y) : x(x), y(y) {}

    bool operator==(const ChunkIndex &other) const
    {
        return x == other.x && y == other.y;
    }
};

// https://stackoverflow.com/a/20602159
struct ChunkIndexHash
{
  public:
    std::size_t operator()(const ChunkIndex &p) const
    {
        return hash_combine(std::hash<int>()(p.x), std::hash<int>()(p.y));
    }

  private:
    // https://stackoverflow.com/a/27952689
    size_t hash_combine(size_t lhs, size_t rhs) const
    {
        return lhs ^ (rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2));
    }
};
