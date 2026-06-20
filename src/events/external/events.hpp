#pragma once

#include "events/external/base.hpp"
#include "identifiers/scene.hpp"
#include "identifiers/sounds.hpp"
#include "px/sound/sound_handler.hpp"
#include "px/time/time_handler.hpp"

struct ExternalPlaySoundEvent : public ExternalEvent
{
    ExternalPlaySoundEvent() : ExternalEvent(ExternalEventType::PlaySound) {}
    virtual ~ExternalPlaySoundEvent() = default;

    SoundID soundID;
    px::SoundPlaySettings settings;
};

struct ExternalChangeSpeedEvent : public ExternalEvent
{
    ExternalChangeSpeedEvent() : ExternalEvent(ExternalEventType::ChangeSpeed) {}
    virtual ~ExternalChangeSpeedEvent() = default;

    px::TimeHandler::SpeedChanger::Settings settings;
};

struct ExternalLoadSceneEvent : public ExternalEvent
{
    ExternalLoadSceneEvent() : ExternalEvent(ExternalEventType::LoadScene) {}
    virtual ~ExternalLoadSceneEvent() = default;

    SceneID id;
};
