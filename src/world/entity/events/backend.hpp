#pragma once

#include "event.hpp"
#include "events/backend.hpp"

struct EntityBackendPlaySoundEvent : public EntityEvent
{
    EntityBackendPlaySoundEvent(const uint64_t caller)
        : EntityEvent(caller, EntityEventType::BackendPlaySound)
    {
    }

    BackendPlaySoundEvent backendEvent;
};
