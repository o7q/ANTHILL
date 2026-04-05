#include "backend/sound/sound.hpp"
#include "assets.hpp"
#include "identifiers/assets/sounds.hpp"

void Assets::initSounds()
{
    std::unordered_map<SoundIDKey, SoundLoadData> sounds;

    sounds[SoundID::WeaponShotgunFire1] = {
        "assets/sounds/weapons/shotgun/fire1.wav"};
    sounds[SoundID::WeaponShotgunFire2] = {
        "assets/sounds/weapons/shotgun/fire2.wav"};
    sounds[SoundID::WeaponShotgunFire3] = {
        "assets/sounds/weapons/shotgun/fire3.wav"};
    sounds[SoundID::WeaponShotgunReload1] = {
        "assets/sounds/weapons/shotgun/reload1.wav"};

    for (auto &[id, data] : sounds)
    {
        m_sounds.add(id, std::make_unique<Sound>(data.path));
    }
}
