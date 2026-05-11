#pragma once

#include "core/texture/texture.hpp"
#include <string>
#include <unordered_map>

class Font
{
  private:
    struct GlyphInfo
    {
        Vec2u size;
        unsigned int xIndex;
        unsigned int baseline;
    };

  public:
    struct TextureGenerateSettings
    {
        const std::string &text;
        Color color           = Color(255, 255, 255);
        int spaceWidth        = 5;
        int horizontalSpacing = 1;
        int verticalSpacing   = 8;
    };

  public:
    Font() = default;
    Font(const std::filesystem::path &path);
    Font(const Font &other)            = delete;
    Font &operator=(const Font &other) = delete;
    ~Font()                            = default;

    GlyphInfo createGlyphIndex(unsigned int atlasXIndex);

    Texture generateTexture(TextureGenerateSettings settings) const;

  private:
    Texture m_atlas;
    const std::string m_charmap = "abcdefghijklmnopqrstuvwxyz1234567890";
    std::unordered_map<char, GlyphInfo> m_glyphInfos;
};
