#pragma once

#include "asset_pool/asset_pool.hpp"
#include "backend/sound/sound.hpp"
#include "identifiers/assets/sounds.hpp"
#include <string>

struct SoundLoadData
{
    std::string path = "";
};

void initSounds(AssetPool<SoundID, Sound> &assets);
