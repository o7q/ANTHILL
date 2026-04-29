#include "sounds.hpp"

void initSounds(AssetPool<SoundIDKey, Sound> &assets)
{
    std::unordered_map<SoundIDKey, SoundLoadData> v;

    v[SoundID::WeaponShotgunFire1]   = {"assets/sounds/weapons/shotgun/fire1.wav"};
    v[SoundID::WeaponShotgunFire2]   = {"assets/sounds/weapons/shotgun/fire2.wav"};
    v[SoundID::WeaponShotgunFire3]   = {"assets/sounds/weapons/shotgun/fire3.wav"};
    v[SoundID::WeaponShotgunReload1] = {"assets/sounds/weapons/shotgun/reload1.wav"};

    for (auto &[id, data] : v)
    {
        assets.add(id, std::make_unique<Sound>(data.path));
    }
}
