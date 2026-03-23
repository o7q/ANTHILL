#include "viewport.hpp"

#include "backend/texture/texture.hpp"
#include "math/line.hpp"
#include <cmath>
#include <optional>

void Viewport::drawSegment(Vec2i p1, Vec2i p2, Color color)
{
    Math::Line::bresenhamLine(p1, p2,
                              [this, &color](int x, int y)
                              {
                                  this->setPixel(x, y, color);
                                  return false;
                              });
}

void Viewport::drawRectOutline(Vec2i p1, Vec2i p2, Color color)
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

void Viewport::drawRectFilled(Vec2i p1, Vec2i p2, Color color)
{
    for (int y = p1.y; y <= p2.y; ++y)
    {
        for (int x = p1.x; x <= p2.x; ++x)
        {
            setPixel(x, y, color);
        }
    }
}

void Viewport::drawTexture(const Texture &texture, Vec2i pos)
{
    Vec2i size = texture.getSize().toInt();
    Vec2i halfSize = size / 2;

    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            Color color = texture.getPixel(x, y);
            setPixel(pos.x - halfSize.x + x, pos.y - halfSize.y + y, color);
        }
    }
}

void Viewport::drawTextureRotated(const Texture &texture, Vec2i pos,
                                  float angle,
                                  std::optional<Vec2i> rotateOrigin,
                                  int overdraw)
{
    Vec2i textureSize = texture.getSize().toInt();
    Vec2i halfTextureSize = textureSize / 2;
    Vec2i origin = rotateOrigin.value_or(halfTextureSize);

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

            for (int py = 0; py < overdraw + 1; ++py)
            {
                for (int px = 0; px < overdraw + 1; ++px)
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
