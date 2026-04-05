#include "scene.hpp"

void Scene::update()
{
    if (m_firstTick)
    {
        onStart();
        m_firstTick = false;
    }

    onTick();

    handleBackendEvents();
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
            r_sound.playSound(*r_assets.sounds().get(event->soundID),
                              event->settings);
        }
        break;
        }
    }

    m_backendEvents.clear();
}
