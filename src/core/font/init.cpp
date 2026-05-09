#include "font.hpp"

Font::Font(const std::filesystem::path &path) : m_atlas(path)
{
    unsigned int atlasXIndex = 0;
    unsigned int charIndex   = 0;
    while (true)
    {
        Color color = m_atlas.getPixel({atlasXIndex, 0});
        if (color.r == 255)
        {
            GlyphInfo info                     = createGlyphIndex(atlasXIndex);
            m_glyphInfos[m_charmap[charIndex]] = info;
            atlasXIndex += info.size.x + 2;
            charIndex++;
        }
        else
        {
            atlasXIndex++;
        }

        if (atlasXIndex >= m_atlas.getSize().x || charIndex >= m_charmap.length())
        {
            break;
        }
    }
}

Font::GlyphInfo Font::createGlyphIndex(unsigned int atlasXIndex)
{
    GlyphInfo info;
    info.xIndex = atlasXIndex;

    // _  0
    // x[]
    //    1
    // 0: width marker
    // 1: height marker
    // x: baseline marker

    unsigned int yIndex = 1;
    while (true)
    {
        if (yIndex >= m_atlas.getSize().y)
        {
            break;
        }

        Color c = m_atlas.getPixel({atlasXIndex, yIndex});

        if (c.g == 255)
        {
            info.baseline = yIndex - 1;
        }

        if (c.r == 255)
        {
            info.size.y = yIndex - 1;
            break;
        }

        ++yIndex;
    }

    unsigned int xIndex = 1;
    while (true)
    {
        if (xIndex >= m_atlas.getSize().x)
        {
            break;
        }

        Color c = m_atlas.getPixel({atlasXIndex + xIndex, yIndex});

        if (c.r == 255)
        {
            info.size.x = xIndex - 1;
            break;
        }

        ++xIndex;
    }

    return info;
}
