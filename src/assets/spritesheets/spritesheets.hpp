#pragma once

#include "px/asset_pool/asset_pool.hpp"
#include "px/math/geometry/vec.hpp"
#include "px/sprite_sheet/sprite_sheet.hpp"
#include "identifiers/spritesheet.hpp"
#include <string>

struct SpriteSheetLoadData
{
    std::string path = "";
    Vec2u size;
};

void initSpriteSheets(AssetPool<SpriteSheetID, SpriteSheet> &assets);
void initSumi(std::unordered_map<SpriteSheetID, SpriteSheetLoadData> &v);
void initEntities(std::unordered_map<SpriteSheetID, SpriteSheetLoadData> &v);
