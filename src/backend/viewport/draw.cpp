#include "viewport.hpp"

#include "backend/texture/texture.hpp"
#include "math/line.hpp"
#include <cmath>
#include <iostream>
#include <optional>

void Viewport::drawSegment(Vec2i p1, Vec2i p2, Color color)
{
    Math::Line::bresenhamLine(p1, p2,
                              [this, &color](Vec2i pos)
                              {
                                  this->setPixel(pos.toUnsignedInt(), color);
                                  return false;
                              });
}

void Viewport::drawRectOutline(Vec2i p1, Vec2i p2, Color color)
{
    // top
    for (int x = p1.x; x < p2.x; ++x)
    {
        setPixel(Vec2u(x, p1.y), color);
    }

    // right
    for (int y = p1.y; y < p2.y; ++y)
    {
        setPixel(Vec2u(p2.x, y), color);
    }

    // bottom
    for (int x = p2.x; x > p1.x; --x)
    {
        setPixel(Vec2u(x, p2.y), color);
    }

    // left
    for (int y = p2.y; y > p1.y; --y)
    {
        setPixel(Vec2u(p1.x, y), color);
    }
}

void Viewport::drawRectFilled(Vec2i p1, Vec2i p2, Color color)
{
    for (int y = p1.y; y <= p2.y; ++y)
    {
        for (int x = p1.x; x <= p2.x; ++x)
        {
            setPixel(Vec2u(x, y), color);
        }
    }
}

void Viewport::drawTexture(const Texture &texture, TextureDrawSettings s)
{
    if (s.rotateSettings.has_value())
    {
        draw_texture_rotated(texture, s);
        return;
    }

    Vec2i textureSize = texture.getSize().toInt();
    Vec2i halfTextureSize = textureSize / 2;
    Vec2i origin = s.origin.value_or(halfTextureSize);

    for (int y = 0; y < textureSize.y; ++y)
    {
        for (int x = 0; x < textureSize.x; ++x)
        {
            Vec2i localPos = Vec2i(x, y) - origin;

            if (s.flipX)
            {
                localPos.x = -localPos.x;
            }
            if (s.flipY)
            {
                localPos.y = -localPos.y;
            }

            Color color = texture.getPixel(Vec2u(x, y));
            Vec2i pixelPlace = s.pos + localPos;
            setPixel(pixelPlace.toUnsignedInt(), color);
        }
    }
}

void Viewport::draw_texture_rotated(const Texture &texture,
                                    TextureDrawSettings s)
{
    TextureRotateSettings rs = s.rotateSettings.value();

    Vec2i textureSize = texture.getSize().toInt();
    Vec2i halfTextureSize = textureSize / 2;
    Vec2i origin = s.origin.value_or(halfTextureSize);

    float cosA = std::cosf(rs.angle);
    float sinA = std::sinf(rs.angle);

    for (int y = 0; y < textureSize.y; ++y)
    {
        for (int x = 0; x < textureSize.x; ++x)
        {
            float dx = x - origin.x;
            float dy = y - origin.y;

            if (s.flipX)
            {
                dx = -dx;
            }
            if (s.flipY)
            {
                dy = -dy;
            }

            float rotatedX = cosA * dx - sinA * dy;
            float rotatedY = sinA * dx + cosA * dy;

            int destX = static_cast<int>(std::roundf(s.pos.x + rotatedX));
            int destY = static_cast<int>(std::roundf(s.pos.y + rotatedY));

            Color color = texture.getPixel(Vec2u(x, y));

            for (int py = 0; py < rs.overdraw + 1; ++py)
            {
                for (int px = 0; px < rs.overdraw + 1; ++px)
                {
                    if (x + px >= textureSize.x || y + py >= textureSize.y)
                    {
                        continue;
                    }

                    int fx = destX + px;
                    int fy = destY + py;
                    setPixel(Vec2u(fx, fy), color);
                }
            }
        }
    }
}
