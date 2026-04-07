#pragma once

#include <functional>

struct Index2D
{
    int x = 0, y = 0;

    Index2D() = default;
    Index2D(int x_, int y_) : x(x_), y(y_) {}

    bool operator==(const Index2D &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Index2D &other) const
    {
        return x != other.x || y != other.y;
    }
};

// https://stackoverflow.com/a/20602159
struct Index2DHash
{
  public:
    std::size_t operator()(const Index2D &p) const
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
