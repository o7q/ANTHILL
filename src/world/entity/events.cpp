#include "entity_handler.hpp"

#include "event/event_emitter.hpp"
#include "events/backend.hpp"
#include "world/entity/events/entity.hpp"
#include "world/entity/events/particle.hpp"
#include "world/particle/events/event.hpp"
#include <memory>

void EntityHandler::handleEvents(Entity *entity)
{
    EventEmitter<EntityEvent> &currentEmitter = entity->getEventEmitter();

    for (auto &event : currentEmitter.getEmittedEvents())
    {
        switch (event->type)
        {
        case EntityEventType::EntityDamage:
        {
            auto e = static_cast<EntityDamageEvent *>(event.get());

            uint64_t target = e->target;
            if (target != 0)
            {
                m_entities[target]->damage(e->damage);
            }
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

    currentEmitter.purge();
}
