#pragma once

#include "asset_pool/asset_pool.hpp"
#include "backend/font/font.hpp"
#include "identifiers/assets/fonts.hpp"
#include <string>

struct FontLoadData
{
    std::string path = "";
};

void initFonts(AssetPool<FontIDKey, Font> &assets);
