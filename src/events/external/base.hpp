#pragma once

enum class ExternalEventType
{
    PlaySound,
    ChangeSpeed,
    LoadScene,
    ShakeCamera
};

struct ExternalEvent
{
    ExternalEvent(ExternalEventType type_) : type(type_) {}
    virtual ~ExternalEvent() = default;

    ExternalEventType type;
};
