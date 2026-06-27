#include "main_scene.hpp"

#include "events/external/events.hpp"

void MainScene::handle_events()
{
    for (auto &e : m_events.getEvents())
    {
        switch (e->type)
        {
        case ExternalEventType::PlaySound:
        {
            auto event = static_cast<ExternalPlaySoundEvent *>(e.get());
            r_instance.sound().playSound(r_assets.sounds().get(event->soundID), event->config);
        }
        break;
        case ExternalEventType::ChangeSpeed:
        {
            auto event = static_cast<ExternalChangeSpeedEvent *>(e.get());
            r_instance.time().getSpeedChanger().startTransition(event->transition);
        }
        break;
        case ExternalEventType::LoadScene:
        {
            auto event = static_cast<ExternalLoadSceneEvent *>(e.get());
            changeScene(event->id);
        }
        break;
        case ExternalEventType::ShakeCamera:
            break;
        }
    }

    m_events.flush();
}