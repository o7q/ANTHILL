#pragma once

#include "identifiers/textures.hpp"
#include "px/asset_pool/asset_pool.hpp"
#include "px/texture/texture.hpp"
#include <string>

struct TextureLoadData
{
    std::string path = "";
};

void initTextures(px::AssetPool<TextureID, px::Texture> &assets);
void initBackgrounds(std::unordered_map<TextureID, TextureLoadData> &v);
