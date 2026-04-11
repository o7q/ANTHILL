#pragma once

#include "math/vec.hpp"
#include "utils/data_structures/index_2d.hpp"
#include <limits>
#include <unordered_map>

namespace Math
{
namespace Voronoi
{

template <typename Data> struct VoronoiSeed
{
    Vec2f localPosition;
    Data data;
};

struct VoronoiSample
{
    float distance = 0.0f;
    Index2D index;
};

// https://www.ronja-tutorials.com/post/028-voronoi-noise
template <typename Data>
inline VoronoiSample
sample(Vec2f pos,
       const std::unordered_map<Index2D, VoronoiSeed<Data>, Index2DHash> &seeds)
{
    Vec2i baseCell = pos.toGrid();

    VoronoiSample out;
    out.distance = std::numeric_limits<float>::max();
    for (int ry = -1; ry <= 1; ++ry)
    {
        for (int rx = -1; rx <= 1; ++rx)
        {
            Vec2i cell = baseCell + Vec2i(rx, ry);
            Index2D cellIndex = Index2D(cell.x, cell.y);

            if (seeds.find(cellIndex) == seeds.end())
            {
                continue;
            }

            Vec2f seedGlobalPos =
                cell.toFloat() + seeds.at(cellIndex).localPosition;

            float dx = seedGlobalPos.x - pos.x;
            float dy = seedGlobalPos.y - pos.y;
            float dist = std::sqrt(dx * dx + dy * dy);

            if (dist < out.distance)
            {
                out.distance = dist;
                out.index = cellIndex;
            }
        }
    }

    return out;
}

template <typename Data>
inline VoronoiSample sampleEx(
    Vec2f pos, Vec2f gridSize,
    const std::unordered_map<Index2D, VoronoiSeed<Data>, Index2DHash> &seeds)
{
    return sample<Data>(pos / gridSize, seeds);
}
} // namespace Voronoi
} // namespace Math
