#pragma once

#include "asset_pool/asset_pool.hpp"
#include "backend/sprite_sheet/sprite_sheet.hpp"
#include "identifiers/assets/spritesheet.hpp"
#include "math/vec.hpp"
#include <string>

struct SpriteSheetLoadData
{
    std::string path = "";
    Vec2u size;
};

void initSpriteSheets(AssetPool<SpriteSheetID, SpriteSheet> &assets);
void initSumi(std::unordered_map<SpriteSheetID, SpriteSheetLoadData> &v);
void initEntities(std::unordered_map<SpriteSheetID, SpriteSheetLoadData> &v);
void initItems(std::unordered_map<SpriteSheetID, SpriteSheetLoadData> &v);
