#pragma once

#include "identifiers/spritesheet.hpp"
#include "px/asset_pool/asset_pool.hpp"
#include "px/basic_types/vec.hpp"
#include "px/sprite_sheet/sprite_sheet.hpp"
#include <string>

struct SpriteSheetLoadData
{
    std::string path = "";
    px::Vec2u size;
};

void initSpriteSheets(px::AssetPool<SpriteSheetID, px::SpriteSheet> &assets);
void initSumi(std::unordered_map<SpriteSheetID, SpriteSheetLoadData> &v);
void initEntities(std::unordered_map<SpriteSheetID, SpriteSheetLoadData> &v);
