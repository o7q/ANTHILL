#pragma once

#include "core/asset_pool/asset_pool.hpp"
#include "core/sound/sound.hpp"
#include "identifiers/assets/sounds.hpp"
#include <string>

struct SoundLoadData
{
    std::string path = "";
};

void initSounds(AssetPool<SoundID, Sound> &assets);
