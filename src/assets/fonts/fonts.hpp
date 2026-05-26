#pragma once

#include "core/asset_pool/asset_pool.hpp"
#include "core/font/font.hpp"
#include "identifiers/fonts.hpp"
#include <string>

struct FontLoadData
{
    std::string path = "";
};

void initFonts(AssetPool<FontID, Font> &assets);
