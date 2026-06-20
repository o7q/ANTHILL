#pragma once

#include "identifiers/fonts.hpp"
#include "px/asset_pool/asset_pool.hpp"
#include "px/font/font.hpp"
#include <string>

struct FontLoadData
{
    std::string path = "";
};

void initFonts(px::AssetPool<FontID, px::Font> &assets);
