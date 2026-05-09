#include "sprite_sheet.hpp"

SpriteSheet::SpriteSheet(const std::filesystem::path &path, Vec2u spriteSize)
{
    Texture spriteSheet(path);

    unsigned int spriteCount = spriteSheet.getSize().x / spriteSize.x;

    for (unsigned int sprite = 0; sprite < spriteCount; ++sprite)
    {
        Texture frame(spriteSize);
        for (unsigned int y = 0; y < spriteSize.y; ++y)
        {
            for (unsigned int x = 0; x < spriteSize.x; ++x)
            {
                Color color = spriteSheet.getPixel({x + spriteSize.x * sprite, y});
                frame.setPixel({x, y}, color);
            }
        }

        m_frames.push_back(frame);
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
