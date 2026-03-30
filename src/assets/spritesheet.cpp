#include "identifiers/spritesheet.hpp"
#include "assets.hpp"
#include "backend/sprite_sheet/sprite_sheet.hpp"

void Assets::initSpriteSheets()
{
    m_spriteSheets.add(SpriteSheetID::CatBoinga,
                       std::make_unique<SpriteSheet>(
                           "assets/images/cat_boinga.png", Vec2u(15, 25)));
}
