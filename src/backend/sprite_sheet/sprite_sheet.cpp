#include "sprite_sheet.hpp"
#include "math/index.hpp"

SpriteSheet::SpriteSheet(const std::filesystem::path &path, Vec2u spriteSize)
{
    Texture spriteSheet(path);

    int spriteCount = spriteSheet.getSize().x / spriteSize.x;

    for (int f = 0; f < spriteCount; ++f)
    {
        std::vector<Color> pixels;
        pixels.resize(spriteSize.x * spriteSize.y);
        for (unsigned int y = 0; y < spriteSize.y; ++y)
        {
            for (unsigned int x = 0; x < spriteSize.x; ++x)
            {
                Color color = spriteSheet.getPixel({x + spriteSize.x * f, y});
                pixels[Math::Index::index_2dto1d({x, y}, spriteSize.x)] = color;
            }
        }

        m_frames.push_back(Texture(pixels, spriteSize));
    }
}

const Texture *SpriteSheet::getSprite(unsigned int index) const
{
    if (index >= m_frames.size())
    {
        return nullptr;
    }

    return &m_frames[index];
}
