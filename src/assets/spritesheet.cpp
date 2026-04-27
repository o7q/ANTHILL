#include "identifiers/assets/spritesheet.hpp"
#include "assets.hpp"
#include "backend/sprite_sheet/sprite_sheet.hpp"

void Assets::initSpriteSheets()
{
    std::unordered_map<SpriteSheetIDKey, SpriteSheetLoadData> spriteSheets;

    spriteSheets[SpriteSheetID::Entity_SumiIdleHead] = {
        "assets/spritesheets/entities/sumi/sumi_idle_head.png", {7, 7}};
    spriteSheets[SpriteSheetID::Entity_SumiIdleHeadUp45] = {
        "assets/spritesheets/entities/sumi/sumi_idle_head_up45.png", {7, 8}};
    spriteSheets[SpriteSheetID::Entity_SumiIdleHeadDown45] = {
        "assets/spritesheets/entities/sumi/sumi_idle_head_down45.png", {7, 9}};
    spriteSheets[SpriteSheetID::Entity_SumiIdleTorso] = {
        "assets/spritesheets/entities/sumi/sumi_idle_torso.png", {4, 8}};
    spriteSheets[SpriteSheetID::Entity_SumiIdleLegs] = {
        "assets/spritesheets/entities/sumi/sumi_idle_legs.png", {3, 8}};
    spriteSheets[SpriteSheetID::Entity_SumiRunHead] = {
        "assets/spritesheets/entities/sumi/sumi_run_head.png", {8, 8}};
    spriteSheets[SpriteSheetID::Entity_SumiRunTorso] = {
        "assets/spritesheets/entities/sumi/sumi_run_torso.png", {11, 8}};
    spriteSheets[SpriteSheetID::Entity_SumiRunLegs] = {
        "assets/spritesheets/entities/sumi/sumi_run_legs.png", {15, 9}};

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
