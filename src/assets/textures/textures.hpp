#pragma once

#include "asset_pool/asset_pool.hpp"
#include "backend/texture/texture.hpp"
#include "identifiers/assets/textures.hpp"
#include <string>

struct TextureLoadData
{
    std::string path = "";
};

void initTextures(AssetPool<TextureID, Texture> &assets);
void initBackgrounds(std::unordered_map<TextureID, TextureLoadData> &v);
