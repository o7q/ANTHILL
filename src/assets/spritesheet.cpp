#include "identifiers/assets/spritesheet.hpp"
#include "assets.hpp"
#include "backend/sprite_sheet/sprite_sheet.hpp"

void Assets::initSpriteSheets()
{
    std::unordered_map<SpriteSheetIDKey, SpriteSheetLoadData> spriteSheets;

    spriteSheets[SpriteSheetID::Entity_SumiIdle] = {
        "assets/spritesheets/entities/sumi/sumi_idle.png", {6, 22}};
    spriteSheets[SpriteSheetID::Entity_SumiRun] = {
        "assets/spritesheets/entities/sumi/sumi_run.png", {15, 22}};
    spriteSheets[SpriteSheetID::Entity_SumiIdleToRun] = {
        "assets/spritesheets/entities/sumi/sumi_idle_to_run.png", {8, 21}};
    spriteSheets[SpriteSheetID::Entity_Wuskkogel] = {
        "assets/spritesheets/entities/wuskkogel/wuskkogel.png", {23, 22}};
    spriteSheets[SpriteSheetID::Item_Shotgun] = {
        "assets/spritesheets/weapons/shotgun/shotgun.png", {22, 12}};

    for (auto &[id, data] : spriteSheets)
    {
        m_spriteSheets.add(id,
                           std::make_unique<SpriteSheet>(data.path, data.size));
    }
}
