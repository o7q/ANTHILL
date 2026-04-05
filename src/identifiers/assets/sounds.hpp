#pragma once

#include "identifiers/identifier.hpp"

enum class SoundID
{
    WeaponShotgunFire1,
    WeaponShotgunFire2,
    WeaponShotgunFire3,
    WeaponShotgunReload1
};
using SoundIDKey = Identifier<SoundID>;
