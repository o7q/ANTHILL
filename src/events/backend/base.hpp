#pragma once

#include "backend/sound/sound_handler.hpp"
#include "identifiers/sounds.hpp"
#include <variant>

struct BackendPlaySoundEvent
{
    BackendPlaySoundEvent() = default;
    virtual ~BackendPlaySoundEvent() = default;

    SoundIDKey soundID;
    SoundPlaySettings settings;
};

using BackendEvent = std::variant<BackendPlaySoundEvent>;
