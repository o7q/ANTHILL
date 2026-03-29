#pragma once

#include <variant>

#include "events/entity/entity_backend.hpp"
#include "events/entity/entity_entity.hpp"
#include "events/entity/entity_particle.hpp"

using EntityEvent =
    std::variant<EntitySpawnEvent, EntityDamageEvent, EntityParticleDrawEvent,
                 EntityBackendPlaySoundEvent>;
