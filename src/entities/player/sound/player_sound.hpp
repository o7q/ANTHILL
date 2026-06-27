#pragma once

#include "px/utils/random.hpp"
#include "px/timer/timer.hpp"
#include "entity/body/entity_body.hpp"
#include "entity/update_context.hpp"
#include "events/entity/base.hpp"
#include "events/entity/events.hpp"
#include "events/event_pool.hpp"
#include "events/external/events.hpp"
#include "identifiers/sounds.hpp"
#include <memory>

class PlayerSound
{
  public:
    struct UpdateData
    {
        const EntityBody &body;
        bool grounded = false;
    };

  public:
    PlayerSound()
    {
        m_strideTimer.setMode(px::Timer::Mode::Repeat);
        m_strideTimer.setDurationInMilliseconds(300);
        m_strideTimer.restart();

        m_groundTimer.setDurationInMilliseconds(200);
    }

    void update(const EntityUpdateContext &context, const UpdateData &data, EventPool<EntityEvent> &eventsOut)
    {
        if (data.grounded)
        {
            m_groundTimer.restart();
        }

        if (std::abs(data.body.getVelocity().x) > 0.2f &&
            data.body.getPosition().x - data.body.getLastPosition().x != 0 && m_groundTimer.active())
        {
            if (m_strideTimer.completed())
            {
                auto soundEvent = std::make_unique<ExternalPlaySoundEvent>();

                SoundID ids[6] = {SoundID::WalkSound1, SoundID::WalkSound2, SoundID::WalkSound3,
                                  SoundID::WalkSound4, SoundID::WalkSound5, SoundID::WalkSound6};

                soundEvent->soundID         = ids[px::Random::unseededRandomInt(0, 6)];
                soundEvent->config.volume = 0.1f;

                eventsOut.emit(std::make_unique<EntityExternalEvent>(context.id, std::move(soundEvent)));
            }
        }
        else
        {
            m_strideTimer.restart();
        }

        m_strideTimer.update(context.time.getDeltaTime());
        m_groundTimer.update(context.time.getDeltaTime());
    }

  private:
    px::Timer m_groundTimer;
    px::Timer m_strideTimer;
};
