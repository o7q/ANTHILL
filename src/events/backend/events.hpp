#pragma once

#include "backend/sound/sound_handler.hpp"
#include "events/backend/base.hpp"
#include "identifiers/assets/sounds.hpp"

struct BackendPlaySoundEvent : public BackendEvent
{
    BackendPlaySoundEvent() : BackendEvent(BackendEventType::PlaySound) {}
    virtual ~BackendPlaySoundEvent() = default;

    SoundIDKey soundID;
    SoundPlaySettings settings;
};
