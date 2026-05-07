#include "scene.hpp"
#include "events/scene/base.hpp"
#include "events/scene/events.hpp"

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
        case SceneEventType::PlaySound:
        {
            auto event = static_cast<ScenePlaySoundEvent *>(e.get());
            r_window.getSound().playSound(r_assets.sounds().get(event->soundID), event->settings);
        }
        break;
        case SceneEventType::ChangeSpeed:
        {
            auto event = static_cast<SceneChangeSpeedEvent *>(e.get());
            r_window.getTime().getSpeedChanger().startTransition(event->settings);
        }
        break;
        case SceneEventType::Load:
        {
            auto event    = static_cast<SceneLoadEvent *>(e.get());
            m_result.load = true;
            m_result.id   = event->id;
        }
        break;
        }
    }

    m_events.flush();
}
