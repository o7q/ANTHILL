#pragma once

#include "math/distance.hpp"
#include "math/random.hpp"
#include "math/vec.hpp"
#include <cstdint>
#include <limits>

namespace Math
{
namespace Voronoi
{
struct Sample
{
    float distance = 0.0f;
    Vec2i cell;
};

enum class Style
{
    Normal,
    Blocky
};

// https://www.ronja-tutorials.com/post/028-voronoi-noise
inline Sample sample(Vec2f pos, uint32_t seed, Style style = Style::Normal)
{
    Vec2i baseCell = pos.toGrid();

    Sample out;
    out.distance = std::numeric_limits<float>::max();
    for (int ry = -1; ry <= 1; ++ry)
    {
        for (int rx = -1; rx <= 1; ++rx)
        {
            Vec2i cell = baseCell + Vec2i(rx, ry);

            constexpr float maxHash =
                static_cast<float>(std::numeric_limits<uint32_t>::max());
            float randomLocalX = Random::hashFromPosition(cell, seed) / maxHash;
            float randomLocalY =
                Random::hashFromPosition(cell, seed + 1) / maxHash;
            Vec2f seedLocalPos = {randomLocalX, randomLocalY};
            Vec2f seedGlobalPos = cell.toFloat() + seedLocalPos;

            float dist = 0.0f;
            switch (style)
            {
            case Style::Normal:
                dist = Math::Distance::euclidian(pos, seedGlobalPos);
                break;
            case Style::Blocky:
                dist = Math::Distance::manhattan(pos, seedGlobalPos);
                break;
            }

            if (dist < out.distance)
            {
                out.distance = dist;
                out.cell = cell;
            }
        }
    }

    return out;
}

inline Sample sampleEx(Vec2f pos, Vec2f gridSize, uint32_t seed = 0,
                       Style style = Style::Normal)
{
    return sample(pos / gridSize, seed, style);
}
} // namespace Voronoi
} // namespace Math
