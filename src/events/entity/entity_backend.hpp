#pragma once

#include "events/backend/base.hpp"
#include "events/entity/base.hpp"

struct EntityBackendPlaySoundEvent : public EntityEvent
{
    EntityBackendPlaySoundEvent(const uint64_t caller)
        : EntityEvent(caller, EntityEventType::BackendPlaySound)
    {
    }

    BackendPlaySoundEvent backendEvent;
};
