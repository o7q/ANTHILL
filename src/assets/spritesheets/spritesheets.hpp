#pragma once

#include "core/asset_pool/asset_pool.hpp"
#include "core/math/vec.hpp"
#include "core/sprite_sheet/sprite_sheet.hpp"
#include "identifiers/assets/spritesheet.hpp"
#include <string>

struct SpriteSheetLoadData
{
    std::string path = "";
    Vec2u size;
};

void initSpriteSheets(AssetPool<SpriteSheetID, SpriteSheet> &assets);
void initSumi(std::unordered_map<SpriteSheetID, SpriteSheetLoadData> &v);
void initEntities(std::unordered_map<SpriteSheetID, SpriteSheetLoadData> &v);
