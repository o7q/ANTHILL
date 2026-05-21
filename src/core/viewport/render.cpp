#include "viewport.hpp"

#include "core/math/bresenham.hpp"
#include "core/utils/variant_bp.hpp"
#include "core/viewport/render_command.hpp"
#include <algorithm>
#include <cmath>
#include <optional>

void Viewport::render(std::vector<RenderCommand> &commands)
{
    std::sort(commands.begin(), commands.end(),
              [](const RenderCommand &a, const RenderCommand &b) { return a.index < b.index; });

    for (const RenderCommand &command : commands)
    {
        std::visit(overloaded{[this](const PointsRenderCommandData &data) { this->render_points(data); },
                              [this](const CircleRenderCommandData &data) { this->render_circle(data); },
                              [this](const SegmentRenderCommandData &data) { this->render_segment(data); },
                              [this](const TriangleRenderCommandData &data) { this->render_triangle(data); },
                              [this](const RectangleRenderCommandData &data) { this->render_rect(data); },
                              [this](const TextureRenderCommandData &data) { this->render_texture(data); }},
                   command.data);
    }
}

void Viewport::render_points(const PointsRenderCommandData &data)
{
    for (Vec2i p : data.points)
    {
        Vec2u viewportSpace = p.toUnsignedInt();
        if (viewportSpace.x >= m_size.x || viewportSpace.y >= m_size.y)
        {
            continue;
        }

        set_pixel(viewportSpace, data.color);
    }
}

void Viewport::render_circle(const CircleRenderCommandData &data)
{
    int radiusSq = data.radius * data.radius;

    for (int ry = -data.radius; ry <= data.radius; ++ry)
    {
        for (int rx = -data.radius; rx <= data.radius; ++rx)
        {
            if (rx * rx + ry * ry <= radiusSq)
            {
                Vec2u viewportPos = (data.pos + Vec2i(rx, ry)).toUnsignedInt();
                set_pixel(viewportPos, data.color);
            }
        }
    }
}

void Viewport::render_segment(const SegmentRenderCommandData &data)
{
    Math::Bresenham::line(data.a, data.b,
                          [this, color = data.color](Vec2i pos)
                          {
                              this->set_pixel(pos.toUnsignedInt(), color);
                              return false;
                          });
}

void Viewport::render_triangle(const TriangleRenderCommandData &data)
{
    SegmentRenderCommandData e[3];

    e[0].a     = data.v0;
    e[0].b     = data.v1;
    e[0].color = data.color;

    e[1].a     = data.v1;
    e[1].b     = data.v2;
    e[1].color = data.color;

    e[2].a     = data.v2;
    e[2].b     = data.v0;
    e[2].color = data.color;

    for (int i = 0; i < 3; ++i)
    {
        render_segment(e[i]);
    }
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
    Vec2i textureSize     = data.texture->getSize().toInt();
    Vec2i halfTextureSize = textureSize / 2;
    Vec2i origin          = {data.origin.first.value_or(halfTextureSize.x),
                             data.origin.second.value_or(halfTextureSize.y)};

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

            Color color      = data.texture->getPixel(Vec2u(x, y));
            Vec2i pixelPlace = data.position + localPos;
            set_pixel(pixelPlace.toUnsignedInt(), color);
        }
    }
}

void Viewport::render_texture_rotated(const TextureRenderCommandData &data)
{
    TextureRenderCommandData::RotateSettings rs = data.rotateSettings.value();

    Vec2u textureSize     = data.texture->getSize();
    Vec2u halfTextureSize = textureSize / 2;
    Vec2i origin          = {data.origin.first.value_or(halfTextureSize.x),
                             data.origin.second.value_or(halfTextureSize.y)};

    float cosA = std::cosf(rs.angle.radians());
    float sinA = std::sinf(rs.angle.radians());

    for (unsigned int y = 0; y < textureSize.y; ++y)
    {
        for (unsigned int x = 0; x < textureSize.x; ++x)
        {
            float dx = static_cast<int>(x) - origin.x;
            float dy = static_cast<int>(y) - origin.y;

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

            int destX = static_cast<int>(std::roundf(data.position.x + rotatedX));
            int destY = static_cast<int>(std::roundf(data.position.y + rotatedY));

            Color color = data.texture->getPixel(Vec2u(x, y));

            for (unsigned int py = 0; py < rs.overdraw + 1; ++py)
            {
                for (unsigned int px = 0; px < rs.overdraw + 1; ++px)
                {
                    if (x + px >= textureSize.x || y + py >= textureSize.y)
                    {
                        continue;
                    }

                    unsigned int fx = destX + px;
                    unsigned int fy = destY + py;
                    set_pixel({fx, fy}, color);
                }
            }
        }
    }
}
