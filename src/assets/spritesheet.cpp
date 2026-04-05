#include "identifiers/assets/spritesheet.hpp"
#include "assets.hpp"
#include "backend/sprite_sheet/sprite_sheet.hpp"

void Assets::initSpriteSheets()
{
    std::unordered_map<SpriteSheetIDKey, SpriteSheetLoadData> spriteSheets;

    spriteSheets[SpriteSheetID::Wuskkogel] = {
        "assets/spritesheets/entities/wuskkogel/wuskkogel.png", {23, 22}};
    spriteSheets[SpriteSheetID::Shotgun] = {
        "assets/spritesheets/weapons/shotgun/shotgun.png", {22, 12}};

    for (auto &[id, data] : spriteSheets)
    {
        m_spriteSheets.add(id,
                           std::make_unique<SpriteSheet>(data.path, data.size));
    }
}
