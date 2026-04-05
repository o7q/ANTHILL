#include "assets.hpp"

void Assets::initSpriteSheets()
{
    m_spriteSheets.add(
        SpriteSheetID::Wuskkogel,
        std::make_unique<SpriteSheet>(
            "assets/spritesheets/wuskkogel/wuskkogel.png", Vec2u(23, 22)));
    m_spriteSheets.add(SpriteSheetID::Shotgun,
                       std::make_unique<SpriteSheet>(
                           "assets/spritesheets/shotgun.png", Vec2u(22, 12)));
}
