#pragma once

#include "backend/sound/sound_handler.hpp"
#include "backend/time/speed_changer.hpp"
#include "events/scene/base.hpp"
#include "identifiers/assets/sounds.hpp"
#include "identifiers/scene.hpp"

struct ScenePlaySoundEvent : public SceneEvent
{
    ScenePlaySoundEvent() : SceneEvent(SceneEventType::PlaySound) {}
    virtual ~ScenePlaySoundEvent() = default;

    SoundIDKey soundID;
    SoundPlaySettings settings;
};

struct SceneChangeSpeedEvent : public SceneEvent
{
    SceneChangeSpeedEvent() : SceneEvent(SceneEventType::ChangeSpeed) {}
    virtual ~SceneChangeSpeedEvent() = default;

    SpeedChanger::Settings settings;
};

struct SceneLoadEvent : public SceneEvent
{
    SceneLoadEvent() : SceneEvent(SceneEventType::Load) {}
    virtual ~SceneLoadEvent() = default;

    SceneIDKey id;
};
