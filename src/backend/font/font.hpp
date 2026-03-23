#pragma once

#include "backend/texture/texture.hpp"
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
    Font() = default;
    Font(const std::filesystem::path &path);
    Font(const Font &other) = delete;
    Font &operator=(const Font &other) = delete;
    ~Font() = default;

    GlyphInfo createGlyphIndex(unsigned int atlasXIndex);

    Texture generateStringTexture(const std::string &text, Color color,
                                  int spaceWidth, int horizontalSpacing,
                                  int verticalSpacing) const;

  private:
    Texture m_atlas;
    const std::string m_charmap = "abcdefghijklmnopqrstuvwxyz1234567890";
    std::unordered_map<char, GlyphInfo> m_glyphInfos;
};
