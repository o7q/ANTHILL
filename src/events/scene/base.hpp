#pragma once

enum class SceneEventType
{
    PlaySound,
    ChangeSpeed,
    Load
};

struct SceneEvent
{
    SceneEvent(SceneEventType type_) : type(type_) {}
    virtual ~SceneEvent() = default;

    SceneEventType type;
};
