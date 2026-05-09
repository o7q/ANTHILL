#pragma once

#include "core/math/angle.hpp"
#include "core/texture/texture.hpp"
#include <optional>
#include <utility>
#include <variant>

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

struct SegmentRenderCommandData
{
    Vec2i a, b;
    Color color;
};

struct RectangleRenderCommandData
{
    Vec2i a, b;
    Color color;
    bool fill = false;
};

struct PointsRenderCommandData
{
    std::vector<Vec2i> points;
    Color color;
};

using RenderCommandData = std::variant<TextureRenderCommandData, SegmentRenderCommandData,
                                       RectangleRenderCommandData, PointsRenderCommandData>;

struct RenderCommand
{
    unsigned int index = 0;
    RenderCommandData data;
};
