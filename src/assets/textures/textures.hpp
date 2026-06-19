#pragma once

#include "px/asset_pool/asset_pool.hpp"
#include "px/texture/texture.hpp"
#include "identifiers/textures.hpp"
#include <string>

struct TextureLoadData
{
    std::string path = "";
};

void initTextures(AssetPool<TextureID, Texture> &assets);
void initBackgrounds(std::unordered_map<TextureID, TextureLoadData> &v);
