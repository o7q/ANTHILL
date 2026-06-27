#include "wuskkogel.hpp"

#include "entities/wuskkogel/ai/states.hpp"
#include "events/entity/events.hpp"
#include "events/external/events.hpp"
#include "px/basic_types/angle.hpp"
#include "px/basic_types/vec.hpp"
#include "px/utils/random.hpp"
#include <memory>

void Wuskkogel::update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
{
    m_lookAngle = px::Angle(m_body.getLastPositionFloat(), m_body.getPositionFloat()).degrees();

    for (DamageSource dd : m_damageSources)
    {
        m_health -= dd.amount;
    }

    UpdateContext updateContext{context,        eventsOut,   m_body,   m_aiPerception,
                                m_aiNavigation, m_lookAngle, m_headPos};
    m_damageSources.clear();

    m_stateMachine.update(updateContext);

    m_bodyHandler.update(context);
    m_animator.update(context.time.getDeltaTime());

    if (m_idleSoundTimer.completed() && m_stateMachine.getCurrentStateID() != WuskkogelStateID::Attack)
    {
        SoundID idleSounds[4] = {SoundID::WuskkogelChirp1, SoundID::WuskkogelChirp2, SoundID::WuskkogelChirp3,
                                 SoundID::WuskkogelChirp4};

        auto soundEvent           = std::make_unique<ExternalPlaySoundEvent>();
        soundEvent->soundID       = idleSounds[px::Random::unseededRandomInt(0, 5)];
        soundEvent->config.volume = 0.1f;
        soundEvent->config.pitch  = px::Random::unseededRandomInt(95, 100) / 100.0f;
        px::Vec2f direction =
            context.vectorTowardsCurrentPlayer * -(context.distanceToCurrentPlayer / 100.0f);
        soundEvent->config.position = direction;

        eventsOut.emit(std::make_unique<EntityExternalEvent>(context.id, std::move(soundEvent)));

        m_idleSoundTimer.setDurationInSeconds(px::Random::unseededRandomInt(5, 10));
        m_idleSoundTimer.restart();
    }

    m_idleSoundTimer.update(context.time.getDeltaTime());
}
