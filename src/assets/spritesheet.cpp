#include "assets.hpp"

void Assets::initSpriteSheets()
{
    m_spriteSheets.add(
        SpriteSheetID::Wuskkogel,
        std::make_unique<SpriteSheet>(
            "assets/spritesheets/wuskkogel/wuskkogel.png", Vec2u(23, 22)));
}
