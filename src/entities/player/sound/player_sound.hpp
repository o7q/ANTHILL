#pragma once

#include "core/math/random.hpp"
#include "core/timer/timer.hpp"
#include "entity/body/entity_body.hpp"
#include "entity/update_context.hpp"
#include "events/external/events.hpp"
#include "identifiers/assets/sounds.hpp"
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
        m_timer.setMode(Timer::Mode::Repeat);
        m_timer.setDurationInMilliseconds(300);
        m_timer.restart();
    }

    std::vector<std::unique_ptr<ExternalPlaySoundEvent>> update(const EntityUpdateContext &context,
                                                                const UpdateData &data)
    {
        std::vector<std::unique_ptr<ExternalPlaySoundEvent>> events;

        if (std::abs(data.body.getVelocity().x) > 0.2f &&
            data.body.getPosition().x - data.body.getLastPosition().x != 0 &&
            (data.grounded || m_timer.active()))
        {
            if (m_timer.completed())
            {
                auto soundEvent = std::make_unique<ExternalPlaySoundEvent>();

                SoundID ids[6] = {SoundID::WalkSound1, SoundID::WalkSound2, SoundID::WalkSound3,
                                  SoundID::WalkSound4, SoundID::WalkSound5, SoundID::WalkSound6};

                soundEvent->soundID         = ids[Math::Random::unseededRandomInt(0, 6)];
                soundEvent->settings.volume = 0.1f;

                events.push_back(std::move(soundEvent));
            }
            m_timer.update(context.time.dt);
        }
        else
        {
            m_timer.restart();
        }

        return events;
    }

  private:
    Timer m_timer;
};
