#include "entity_handler.hpp"

#include "events/entity/entity_backend.hpp"
#include "events/entity/entity_entity.hpp"
#include "events/entity/entity_particle.hpp"
#include "events/event_emitter.hpp"
#include <memory>

void EntityHandler::handleEvents(Entity *entity)
{
    EventEmitter<EntityEvent> &currentEmitter = entity->getEventEmitter();

    for (auto &event : currentEmitter.getEmittedEvents())
    {
        std::visit(overloaded{[&](const EntityDamageEvent &e)
                              {
                                  uint64_t target = e.target;
                                  if (target == 0)
                                  {
                                      return;
                                  }
                                  m_entities[target]->damage(e.damage);
                              },
                              [&](const EntitySpawnEvent &e)
                              {
                                  m_entitiesToAdd.push_back(
                                      e.entityFactory(m_idHandler.getNext()));
                              },
                              [&](const EntityParticleDrawEvent &e)
                              { r_particleEvents.emit(e.particleEvent); },
                              [&](const EntityBackendPlaySoundEvent &e)
                              { r_backendEvents.emit(e.backendEvent); }},
                   event);
    }

    currentEmitter.purge();
}
