#pragma once

#include "identifiers/sounds.hpp"
#include "px/asset_pool/asset_pool.hpp"
#include "px/sound/sound.hpp"
#include <string>

struct SoundLoadData
{
    std::string path = "";
};

void initSounds(px::AssetPool<SoundID, px::Sound> &assets);
