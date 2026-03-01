#pragma once

#include "backend/types/color.hpp"
#include "backend/types/vec.hpp"
#include "backend/viewport.hpp"
#include "utils/math/line.hpp"

namespace Utils
{
namespace Render
{
inline void drawSegment(Viewport &viewport, Vec2<int> p1, Vec2<int> p2,
                        Color color)
{
    auto draw = [&](int x, int y)
    {
        viewport.setPixel(x, y, color);
        return true;
    };
    Utils::Math::Line::bresenhamLine(p1, p2, draw);
}

inline void drawRectOutline(Viewport &viewport, Vec2<int> p1, Vec2<int> p2,
                            Color color)
{
    // top
    for (int x = p1.x; x < p2.x; ++x)
    {
        viewport.setPixel(x, p1.y, color);
    }

    // right
    for (int y = p1.y; y < p2.y; ++y)
    {
        viewport.setPixel(p2.x, y, color);
    }

    // bottom
    for (int x = p2.x; x > p1.x; --x)
    {
        viewport.setPixel(x, p2.y, color);
    }

    // left
    for (int y = p2.y; y > p1.y; --y)
    {
        viewport.setPixel(p1.x, y, color);
    }
}

inline void drawRectFilled(Viewport &viewport, Vec2<int> p1, Vec2<int> p2,
                           Color color)
{
    for (int y = p1.y; y <= p2.y; ++y)
    {
        for (int x = p1.x; x <= p2.x; ++x)
        {
            viewport.setPixel(x, y, color);
        }
    }
}
} // namespace Render
} // namespace Utils
