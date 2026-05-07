#include "scene.hpp"
#include "events/backend/events.hpp"

Scene::Result Scene::update()
{
    if (m_firstTick)
    {
        onStart();
        m_firstTick = false;
    }

    onTick();
    handleBackendEvents();

    return m_result;
}

void Scene::handleBackendEvents()
{
    for (auto &e : m_backendEvents.getEvents())
    {
        switch (e->type)
        {
        case BackendEventType::PlaySound:
        {
            auto event = static_cast<BackendPlaySoundEvent *>(e.get());
            r_window.getSound().playSound(r_assets.sounds().get(event->soundID), event->settings);
        }
        break;
        }
    }

    m_backendEvents.flush();
}
