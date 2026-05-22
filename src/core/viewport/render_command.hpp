#pragma once

#include "core/math/angle.hpp"
#include "core/math/geometry/vec.hpp"
#include "core/texture/texture.hpp"
#include <optional>
#include <utility>
#include <variant>

struct PointsRenderCommandData
{
    std::vector<Vec2i> points;
    Color color;
};

struct CircleRenderCommandData
{
    Vec2i pos;
    int radius = 5;
    Color color;
};

struct SegmentRenderCommandData
{
    Vec2i a, b;
    Color color;
};

struct TriangleRenderCommandData
{
    Vec2i vertices[3];
    Color color;
};

struct RectangleRenderCommandData
{
    Vec2i a, b;
    Color color;
    bool fill = false;
};

struct TextureRenderCommandData
{
    struct RotateSettings
    {
        Angle angle;
        unsigned int overdraw = 1;
    };

    const Texture *texture = nullptr;
    Vec2i position;
    std::pair<std::optional<int>, std::optional<int>> origin;
    bool flipX = false, flipY = false;
    std::optional<RotateSettings> rotateSettings;
};

using RenderCommandData =
    std::variant<PointsRenderCommandData, CircleRenderCommandData, SegmentRenderCommandData,
                 TriangleRenderCommandData, RectangleRenderCommandData, TextureRenderCommandData>;

struct RenderCommand
{
    unsigned int index = 0;
    RenderCommandData data;
};
