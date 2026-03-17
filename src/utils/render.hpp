#pragma once

#include "backend/utils/color.hpp"
#include "backend/utils/vec.hpp"
#include "backend/viewport.hpp"
#include "texture/texture.hpp"
#include "utils/math/angle.hpp"
#include "utils/math/line.hpp"
#include <iostream>
#include <optional>

namespace Utils
{
namespace Render
{
inline void drawSegment(Viewport &viewport, Vec2<int> p1, Vec2<int> p2,
                        Color color)
{
    Utils::Math::Line::bresenhamLine(p1, p2,
                                     [&viewport, &color](int x, int y)
                                     {
                                         viewport.setPixel(x, y, color);
                                         return false;
                                     });
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

inline void drawRectOutlineRotated(Viewport &viewport, Vec2<int> p1,
                                   Vec2<int> p2,
                                   std::optional<Vec2<int>> rotationPoint,
                                   float angle, Color color)
{
    Vec2<int> rotPoint =
        rotationPoint.has_value() ? rotationPoint.value() : (p2 - p1) / 2 + p1;

    Vec2<int> c1 = p1;
    Vec2<int> c2 = {p2.x, p1.y};
    Vec2<int> c3 = p2;
    Vec2<int> c4 = {p1.x, p2.y};

    c1 = Math::Angle::rotatePoint(rotPoint.toFloat(), c1.toFloat(), angle)
             .toGrid();
    c2 = Math::Angle::rotatePoint(rotPoint.toFloat(), c2.toFloat(), angle)
             .toGrid();
    c3 = Math::Angle::rotatePoint(rotPoint.toFloat(), c3.toFloat(), angle)
             .toGrid();
    c4 = Math::Angle::rotatePoint(rotPoint.toFloat(), c4.toFloat(), angle)
             .toGrid();

    drawSegment(viewport, c1, c2, color);
    drawSegment(viewport, c2, c3, color);
    drawSegment(viewport, c3, c4, color);
    drawSegment(viewport, c4, c1, color);
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

inline void drawTexture(Viewport &viewport, const Texture &texture,
                        Vec2<int> pos)
{
    Vec2<int> size = texture.getSize().toInt();
    Vec2<int> halfSize = size / 2;

    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            Color color = texture.getPixel(x, y);
            viewport.setPixel(pos.x - halfSize.x + x, pos.y - halfSize.y + y,
                              color);
        }
    }
}

inline void drawTextureRotated(Viewport &viewport, const Texture &texture,
                               Vec2<int> pos,
                               std::optional<Vec2<int>> rotationPoint,
                               float angle)
{

    Vec2<int> size = texture.getSize().toInt();
    Vec2<int> halfSize = size / 2;

    Vec2<int> rotPoint =
        rotationPoint.has_value() ? rotationPoint.value() : pos;

    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            Vec2<int> point = {pos.x - halfSize.x + x, pos.y - halfSize.y + y};
            point = Math::Angle::rotatePoint(rotPoint.toFloat(),
                                             point.toFloat(), angle)
                        .toGrid();

            Color color = texture.getPixel(x, y);
            viewport.setPixel(point.x, point.y, color);
        }
    }
}
} // namespace Render
} // namespace Utils
