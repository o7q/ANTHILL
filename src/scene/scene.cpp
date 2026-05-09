#include "scene.hpp"
#include "events/external/base.hpp"
#include "events/external/events.hpp"

Scene::Result Scene::update()
{
    if (m_firstTick)
    {
        onStart();
        m_firstTick = false;
    }

    onTick();
    handle_events();

    return m_result;
}

void Scene::handle_events()
{
    for (auto &e : m_events.getEvents())
    {
        switch (e->type)
        {
        case ExternalEventType::PlaySound:
        {
            auto event = static_cast<ExternalPlaySoundEvent *>(e.get());
            r_window.getSound().playSound(r_assets.sounds().get(event->soundID), event->settings);
        }
        break;
        case ExternalEventType::ChangeSpeed:
        {
            auto event = static_cast<ExternalChangeSpeedEvent *>(e.get());
            r_window.getTime().getSpeedChanger().startTransition(event->settings);
        }
        break;
        case ExternalEventType::LoadScene:
        {
            auto event    = static_cast<ExternalLoadSceneEvent *>(e.get());
            m_result.load = true;
            m_result.id   = event->id;
        }
        break;
        case ExternalEventType::ShakeCamera:
            break;
        }
    }

    m_events.flush();
}
