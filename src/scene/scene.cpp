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

    for (auto &e : m_backendEvents.getEmittedEvents())
    {
        switch (e->type)
        {
        case BackendEventType::PlaySound:
        {
            auto event = static_cast<BackendPlaySoundEvent *>(e.get());
            r_sound.playSound(*r_assets.sounds().get(event->soundID),
                              event->settings);
        }
        break;
        }
    }

    m_backendEvents.purge();
}
