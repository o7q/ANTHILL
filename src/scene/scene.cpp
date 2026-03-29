#include "scene.hpp"
#include "events/backend/base.hpp"
#include "events/event_emitter.hpp"

void Scene::update()
{
    if (m_firstTick)
    {
        onStart();
        m_firstTick = false;
    }

    onTick();

    for (auto &event : m_backendEvents.getEmittedEvents())
    {
        std::visit(overloaded{[&](const BackendPlaySoundEvent &e)
                              {
                                  r_sound.playSound(
                                      *r_assets.sounds().get(e.soundID),
                                      e.settings);
                              }},
                   event);
    }

    m_backendEvents.purge();
}
