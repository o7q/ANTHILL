#pragma once

#include "px/asset_pool/asset_pool.hpp"
#include "px/sound/sound.hpp"
#include "identifiers/sounds.hpp"
#include <string>

struct SoundLoadData
{
    std::string path = "";
};

void initSounds(AssetPool<SoundID, Sound> &assets);
