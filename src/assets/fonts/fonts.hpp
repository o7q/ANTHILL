#pragma once

#include "px/asset_pool/asset_pool.hpp"
#include "px/font/font.hpp"
#include "identifiers/fonts.hpp"
#include <string>

struct FontLoadData
{
    std::string path = "";
};

void initFonts(AssetPool<FontID, Font> &assets);
