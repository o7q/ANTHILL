#include "sounds.hpp"

void initSounds(AssetPool<SoundID, Sound> &assets)
{
    std::unordered_map<SoundID, SoundLoadData> v;

    v[SoundID::WalkSound1] = {"assets/sounds/walk/sand/walk_sand1.wav"};
    v[SoundID::WalkSound2] = {"assets/sounds/walk/sand/walk_sand2.wav"};
    v[SoundID::WalkSound3] = {"assets/sounds/walk/sand/walk_sand3.wav"};
    v[SoundID::WalkSound4] = {"assets/sounds/walk/sand/walk_sand4.wav"};
    v[SoundID::WalkSound5] = {"assets/sounds/walk/sand/walk_sand5.wav"};
    v[SoundID::WalkSound6] = {"assets/sounds/walk/sand/walk_sand6.wav"};

    for (auto &[id, data] : v)
    {
        assets.add(id, std::make_unique<Sound>(data.path));
    }
}
