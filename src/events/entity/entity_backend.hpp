#pragma once

#include "events/backend/base.hpp"

struct EntityBackendPlaySoundEvent
{
    EntityBackendPlaySoundEvent(const uint64_t caller) : caller(caller) {}

    const uint64_t caller;
    BackendPlaySoundEvent backendEvent;
};
