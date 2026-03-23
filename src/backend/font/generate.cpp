#include "font.hpp"
#include "math/index.hpp"

#include <limits>

Texture Font::generateStringTexture(const std::string &text, Color color,
                                    int spaceWidth, int horizontalSpacing,
                                    int verticalSpacing) const
{
    std::vector<Vec2i> sparseRaster;

    Vec2i current;
    Vec2i a = {std::numeric_limits<int>::max(),
               std::numeric_limits<int>::max()};
    Vec2i b = {std::numeric_limits<int>::min(),
               std::numeric_limits<int>::min()};

    for (char c : text)
    {
        bool skip = true;
        switch (c)
        {
        case '\n':
            current.x = 0;
            current.y += verticalSpacing;
            break;
        case ' ':
            current.x += spaceWidth;
            break;
        default:
            skip = false;
            break;
        }

        if (skip)
        {
            continue;
        }

        if (m_glyphInfos.find(c) == m_glyphInfos.end())
        {
            continue;
        }

        GlyphInfo info = m_glyphInfos.at(c);

        int yBaselineOffset = info.size.y - info.baseline - 1;

        int ix = current.x;
        int iy = current.y - yBaselineOffset;

        for (unsigned int y = 0; y < info.size.y; ++y)
        {
            for (unsigned int x = 0; x < info.size.x; ++x)
            {
                bool on = m_atlas.getPixel(x + info.xIndex + 1, y + 1).a != 0;

                if (on)
                {
                    Vec2i rasterIndex;
                    rasterIndex.x = ix + x;
                    rasterIndex.y = iy + y;
                    sparseRaster.push_back(rasterIndex);

                    a.x = std::min(a.x, rasterIndex.x);
                    a.y = std::min(a.y, rasterIndex.y);
                    b.x = std::max(b.x, rasterIndex.x);
                    b.y = std::max(b.y, rasterIndex.y);
                }
            }
        }

        current.x += info.size.x + horizontalSpacing;
    }

    if (sparseRaster.empty())
    {
        return Texture();
    }

    Vec2u size;
    size.x = b.x - a.x + 1;
    size.y = b.y - a.y + 1;

    std::vector<Color> pixels(size.x * size.y);

    for (Vec2i i : sparseRaster)
    {
        int x = i.x - a.x;
        int y = i.y - a.y;

        pixels[Math::Index::index_2dto1d(x, y, size.x)] = color;
    }

    Texture texture(pixels, size.x, size.y);
    return texture;
}
