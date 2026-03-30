#include "entity_handler.hpp"

#include "events/entity/entity_backend.hpp"
#include "events/entity/entity_entity.hpp"
#include "events/entity/entity_particle.hpp"
#include "events/event_emitter.hpp"
#include <memory>

void EntityHandler::handleEvents(EventEmitter<EntityEvent> &emitter)
{
    for (auto &event : emitter.getEmittedEvents())
    {
        switch (event->type)
        {
        case EntityEventType::EntityDamage:
        {
            auto e = static_cast<EntityDamageEvent *>(event.get());

            uint64_t target = e->target;
            if (target == 0)
            {
                break;
            }
            m_entities[target]->damage(e->damage);
        }
        break;
        case EntityEventType::EntitySpawn:
        {
            auto e = static_cast<EntitySpawnEvent *>(event.get());
            m_entitiesToAdd.push_back(e->entityFactory(m_idHandler.getNext()));
        }
        break;
        case EntityEventType::ParticleDraw:
        {
            auto e = static_cast<EntityParticleDrawEvent *>(event.get());
            r_particleEvents.emit(
                std::make_unique<ParticleDrawEvent>(e->particleEvent));
        }
        break;
        case EntityEventType::BackendPlaySound:
        {
            auto e = static_cast<EntityBackendPlaySoundEvent *>(event.get());
            r_backendEvents.emit(
                std::make_unique<BackendPlaySoundEvent>(e->backendEvent));
        }
        break;
        }
    }

    emitter.purge();
}
