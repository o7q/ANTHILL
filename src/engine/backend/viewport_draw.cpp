#include "viewport.hpp"

void Viewport::drawTexture(const Texture &texture, unsigned int x,
                           unsigned int y)
{
    Vec2<unsigned int> textureSize = texture.getSize();
    Vec2<unsigned int> textureSizeHalf = texture.getSize() / 2;
    for (unsigned int ty = 0; ty < textureSize.y; ++ty)
    {
        for (unsigned int tx = 0; tx < textureSize.x; ++tx)
        {
            Color color = texture.getPixel(tx, ty);
            setPixel(tx + x - textureSizeHalf.x, ty + y - textureSizeHalf.y,
                     color);
        }
    }
}

void Viewport::drawSegment(Vec2<int> p1, Vec2<int> p2, Color color)
{
    auto draw = [&](int x, int y)
    {
        setPixel(x, y, color);
        return true;
    };
    BackendUtils::Math::bresenhamLine(p1, p2, draw);
}
