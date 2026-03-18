#include "viewport.hpp"

#include "backend/texture/texture.hpp"
#include "math/line.hpp"
#include <cmath>
#include <optional>

void Viewport::drawSegment(Vec2<int> p1, Vec2<int> p2, Color color)
{
    Math::Line::bresenhamLine(p1, p2,
                              [this, &color](int x, int y)
                              {
                                  this->setPixel(x, y, color);
                                  return false;
                              });
}

void Viewport::drawRectOutline(Vec2<int> p1, Vec2<int> p2, Color color)
{
    // top
    for (int x = p1.x; x < p2.x; ++x)
    {
        setPixel(x, p1.y, color);
    }

    // right
    for (int y = p1.y; y < p2.y; ++y)
    {
        setPixel(p2.x, y, color);
    }

    // bottom
    for (int x = p2.x; x > p1.x; --x)
    {
        setPixel(x, p2.y, color);
    }

    // left
    for (int y = p2.y; y > p1.y; --y)
    {
        setPixel(p1.x, y, color);
    }
}

void Viewport::drawRectFilled(Vec2<int> p1, Vec2<int> p2, Color color)
{
    for (int y = p1.y; y <= p2.y; ++y)
    {
        for (int x = p1.x; x <= p2.x; ++x)
        {
            setPixel(x, y, color);
        }
    }
}

void Viewport::drawTexture(const Texture &texture, Vec2<int> pos)
{
    Vec2<int> size = texture.getSize().toInt();
    Vec2<int> halfSize = size / 2;

    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            Color color = texture.getPixel(x, y);
            setPixel(pos.x - halfSize.x + x, pos.y - halfSize.y + y, color);
        }
    }
}

void Viewport::drawTextureRotated(const Texture &texture, Vec2<int> pos,
                                  float angle,
                                  std::optional<Vec2<int>> rotateOrigin)
{
    Vec2<int> textureSize = texture.getSize().toInt();
    Vec2<int> halfTextureSize = textureSize / 2;
    Vec2<int> origin = rotateOrigin.value_or(halfTextureSize);

    float cosA = std::cosf(angle);
    float sinA = std::sinf(angle);

    for (int y = 0; y < textureSize.y; ++y)
    {
        for (int x = 0; x < textureSize.x; ++x)
        {
            float dx = x - origin.x;
            float dy = y - origin.y;

            float rotatedX = cosA * dx - sinA * dy;
            float rotatedY = sinA * dx + cosA * dy;

            int destX = static_cast<int>(
                std::roundf(pos.x + rotatedX + origin.x - halfTextureSize.x));
            int destY = static_cast<int>(
                std::roundf(pos.y + rotatedY + origin.y - halfTextureSize.y));

            Color color = texture.getPixel(x, y);

            for (int py = 0; py < 2; ++py)
            {
                for (int px = 0; px < 2; ++px)
                {
                    if (x + px >= textureSize.x || y + py >= textureSize.y)
                    {
                        continue;
                    }

                    int fx = destX + px;
                    int fy = destY + py;
                    setPixel(fx, fy, color);
                }
            }
        }
    }
}
