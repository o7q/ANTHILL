#pragma once

#include "backend/sound/sound_handler.hpp"
#include "identifiers/sounds.hpp"

enum class BackendEventType
{
    PlaySound
};

struct BackendEvent
{
    BackendEvent(BackendEventType type) : type(type) {}
    virtual ~BackendEvent() = default;

    BackendEventType type;
};

struct BackendPlaySoundEvent : public BackendEvent
{
    BackendPlaySoundEvent() : BackendEvent(BackendEventType::PlaySound) {}
    virtual ~BackendPlaySoundEvent() = default;

    SoundIDKey soundID;
    SoundPlaySettings settings;
};
