#pragma once

#include "px/sound/sound_handler.hpp"
#include "px/time/speed_changer.hpp"
#include "events/external/base.hpp"
#include "identifiers/sounds.hpp"
#include "identifiers/scene.hpp"

struct ExternalPlaySoundEvent : public ExternalEvent
{
    ExternalPlaySoundEvent() : ExternalEvent(ExternalEventType::PlaySound) {}
    virtual ~ExternalPlaySoundEvent() = default;

    SoundID soundID;
    SoundPlaySettings settings;
};

struct ExternalChangeSpeedEvent : public ExternalEvent
{
    ExternalChangeSpeedEvent() : ExternalEvent(ExternalEventType::ChangeSpeed) {}
    virtual ~ExternalChangeSpeedEvent() = default;

    SpeedChanger::Settings settings;
};

struct ExternalLoadSceneEvent : public ExternalEvent
{
    ExternalLoadSceneEvent() : ExternalEvent(ExternalEventType::LoadScene) {}
    virtual ~ExternalLoadSceneEvent() = default;

    SceneID id;
};
