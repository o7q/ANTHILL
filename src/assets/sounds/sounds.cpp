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

    v[SoundID::WuskkogelAttack1] = {"assets/sounds/entities/wuskkogel/attack1.wav"};
    v[SoundID::WuskkogelAttack2] = {"assets/sounds/entities/wuskkogel/attack2.wav"};
    v[SoundID::WuskkogelAttack3] = {"assets/sounds/entities/wuskkogel/attack3.wav"};
    v[SoundID::WuskkogelAttack4] = {"assets/sounds/entities/wuskkogel/attack4.wav"};
    v[SoundID::WuskkogelAttack5] = {"assets/sounds/entities/wuskkogel/attack5.wav"};
    v[SoundID::WuskkogelChirp1]  = {"assets/sounds/entities/wuskkogel/chirp1.wav"};
    v[SoundID::WuskkogelChirp2]  = {"assets/sounds/entities/wuskkogel/chirp2.wav"};
    v[SoundID::WuskkogelChirp3]  = {"assets/sounds/entities/wuskkogel/chirp3.wav"};
    v[SoundID::WuskkogelChirp4]  = {"assets/sounds/entities/wuskkogel/chirp4.wav"};

    for (auto &[id, data] : v)
    {
        assets.add(id, std::make_unique<Sound>(data.path));
    }
}
