#include "wuskkogel.hpp"

#include "core/math/random.hpp"
#include "entities/wuskkogel/ai/states.hpp"
#include "events/entity/events.hpp"
#include "events/external/events.hpp"
#include <memory>

void Wuskkogel::update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
{
    m_lookAngle =
        Math::Angle::vectorsToAngle(m_body.getLastPositionFloat(), m_body.getPositionFloat()).degrees();

    for (DamageSource dd : m_damageSources)
    {
        m_health -= dd.amount;
    }

    UpdateContext updateContext{context,        eventsOut,   m_body,   m_aiPerception,
                                m_aiNavigation, m_lookAngle, m_headPos};
    m_damageSources.clear();

    m_stateMachine.update(updateContext);

    m_bodyHandler.update(context);
    m_animator.update(context.time.dt);

    if (m_idleSoundTimer.completed() && m_stateMachine.getCurrentStateID() != WuskkogelStateID::Attack)
    {
        SoundID idleSounds[4] = {SoundID::WuskkogelChirp1, SoundID::WuskkogelChirp2, SoundID::WuskkogelChirp3,
                                 SoundID::WuskkogelChirp4};

        auto soundEvent             = std::make_unique<ExternalPlaySoundEvent>();
        soundEvent->soundID         = idleSounds[Math::Random::unseededRandomInt(0, 5)];
        soundEvent->settings.volume = 0.1f;
        soundEvent->settings.pitch  = Math::Random::unseededRandomInt(95, 100) / 100.0f;
        soundEvent->settings.position =
            context.vectorTowardsCurrentPlayer * -(context.distanceToCurrentPlayer / 100.0f);
        eventsOut.emit(std::make_unique<EntityExternalEvent>(context.id, std::move(soundEvent)));

        m_idleSoundTimer.setDurationInSeconds(Math::Random::unseededRandomInt(5, 10));
        m_idleSoundTimer.restart();
    }

    m_idleSoundTimer.update(context.time.dt);
}
