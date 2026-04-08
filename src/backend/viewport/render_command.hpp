#pragma once

#include "backend/texture/texture.hpp"
#include <optional>
#include <variant>

struct TextureRenderCommandData
{
    struct RotateSettings
    {
        float angle = 0.0f;
        unsigned int overdraw = 1;
    };

    const Texture *texture = nullptr;
    Vec2i position;
    std::optional<Vec2i> origin;
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

using RenderCommandData =
    std::variant<TextureRenderCommandData, SegmentRenderCommandData,
                 RectangleRenderCommandData, PointsRenderCommandData>;

struct RenderCommand
{
    unsigned int index = 0;
    RenderCommandData data;
};
