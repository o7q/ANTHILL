#include "backend/viewport/render_command.hpp"
#include "viewport.hpp"

#include "math/line.hpp"
#include "utils/variant_bp.hpp"
#include <algorithm>
#include <cmath>
#include <optional>

void Viewport::render(std::vector<RenderCommand> &commands)
{
    std::sort(commands.begin(), commands.end(),
              [](const RenderCommand &a, const RenderCommand &b)
              { return a.index < b.index; });

    for (const RenderCommand &command : commands)
    {
        renderDirect(command.data);
    }
}

void Viewport::renderDirect(const RenderCommandData &data)
{
    std::visit(overloaded{[this](const TextureRenderCommandData &data)
                          { this->render_texture(data); },
                          [this](const SegmentRenderCommandData &data)
                          { this->render_segment(data); },
                          [this](const RectangleRenderCommandData &data)
                          { this->render_rect(data); }},
               data);
}

void Viewport::render_segment(const SegmentRenderCommandData &data)
{
    Math::Line::bresenhamLine(data.a, data.b,
                              [this, color = data.color](Vec2i pos)
                              {
                                  this->set_pixel(pos.toUnsignedInt(), color);
                                  return false;
                              });
}

void Viewport::render_rect(const RectangleRenderCommandData &data)
{
    if (data.fill)
    {
        render_rect_fill(data);
    }
    else
    {
        render_rect_outline(data);
    }
}

void Viewport::render_rect_fill(const RectangleRenderCommandData &data)
{
    for (int y = data.a.y; y <= data.b.y; ++y)
    {
        for (int x = data.a.x; x <= data.b.x; ++x)
        {
            set_pixel(Vec2u(x, y), data.color);
        }
    }
}

void Viewport::render_rect_outline(const RectangleRenderCommandData &data)
{
    // top
    for (int x = data.a.x; x < data.b.x; ++x)
    {
        set_pixel(Vec2u(x, data.a.y), data.color);
    }

    // right
    for (int y = data.a.y; y < data.b.y; ++y)
    {
        set_pixel(Vec2u(data.b.x, y), data.color);
    }

    // bottom
    for (int x = data.b.x; x > data.a.x; --x)
    {
        set_pixel(Vec2u(x, data.b.y), data.color);
    }

    // left
    for (int y = data.b.y; y > data.a.y; --y)
    {
        set_pixel(Vec2u(data.a.x, y), data.color);
    }
}

void Viewport::render_texture(const TextureRenderCommandData &data)
{
    if (data.rotateSettings.has_value())
    {
        render_texture_rotated(data);
    }
    else
    {
        render_texture_basic(data);
    }
}

void Viewport::render_texture_basic(const TextureRenderCommandData &data)
{
    Vec2i textureSize = data.texture->getSize().toInt();
    Vec2i halfTextureSize = textureSize / 2;
    Vec2i origin = data.origin.value_or(halfTextureSize);

    for (int y = 0; y < textureSize.y; ++y)
    {
        for (int x = 0; x < textureSize.x; ++x)
        {
            Vec2i localPos = Vec2i(x, y) - origin;

            if (data.flipX)
            {
                localPos.x = -localPos.x;
            }
            if (data.flipY)
            {
                localPos.y = -localPos.y;
            }

            Color color = data.texture->getPixel(Vec2u(x, y));
            Vec2i pixelPlace = data.position + localPos;
            set_pixel(pixelPlace.toUnsignedInt(), color);
        }
    }
}

void Viewport::render_texture_rotated(const TextureRenderCommandData &data)
{
    TextureRenderCommandData::RotateSettings rs = data.rotateSettings.value();

    Vec2i textureSize = data.texture->getSize().toInt();
    Vec2i halfTextureSize = textureSize / 2;
    Vec2i origin = data.origin.value_or(halfTextureSize);

    float cosA = std::cosf(rs.angle);
    float sinA = std::sinf(rs.angle);

    for (int y = 0; y < textureSize.y; ++y)
    {
        for (int x = 0; x < textureSize.x; ++x)
        {
            float dx = x - origin.x;
            float dy = y - origin.y;

            if (data.flipX)
            {
                dx = -dx;
            }
            if (data.flipY)
            {
                dy = -dy;
            }

            float rotatedX = cosA * dx - sinA * dy;
            float rotatedY = sinA * dx + cosA * dy;

            int destX =
                static_cast<int>(std::roundf(data.position.x + rotatedX));
            int destY =
                static_cast<int>(std::roundf(data.position.y + rotatedY));

            Color color = data.texture->getPixel(Vec2u(x, y));

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
                    set_pixel(Vec2u(fx, fy), color);
                }
            }
        }
    }
}
