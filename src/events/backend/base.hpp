#pragma once

enum class BackendEventType
{
    PlaySound
};

struct BackendEvent
{
    BackendEvent(BackendEventType type_) : type(type_) {}
    virtual ~BackendEvent() = default;

    BackendEventType type;
};
