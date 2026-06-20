#include "attack.hpp"

#include "px/utils/random.hpp"
#include "entities/player/player.hpp"
#include "events/entity/events.hpp"
#include "events/external/events.hpp"
#include <memory>

WuskkogelStateID WuskkogelAttackState::update(const UpdateContext &context)
{
    const Player *player = context.context.currentPlayer;

    if (!player)
    {
        return WuskkogelStateID::Roam;
    }

    px::Vec2f vec = context.context.vectorTowardsCurrentPlayer * 8.0f;

    if (!m_attackTimer.active())
    {
        context.body.setVelocity(vec);
        m_attackTimer.restart();
        m_attacked = false;

        SoundID biteSounds[5] = {SoundID::WuskkogelAttack1, SoundID::WuskkogelAttack2,
                                 SoundID::WuskkogelAttack3, SoundID::WuskkogelAttack4,
                                 SoundID::WuskkogelAttack5};

        auto soundEvent             = std::make_unique<ExternalPlaySoundEvent>();
        soundEvent->soundID         = biteSounds[px::Utils::Random::unseededRandomInt(0, 5)];
        soundEvent->settings.volume = 0.1f;
        soundEvent->settings.pitch  = px::Utils::Random::unseededRandomInt(95, 100) / 100.0f;
        soundEvent->settings.position =
            context.context.vectorTowardsCurrentPlayer * -(context.context.distanceToCurrentPlayer / 100.0f);
        context.events.emit(std::make_unique<EntityExternalEvent>(context.context.id, std::move(soundEvent)));
    }

    m_attackTimer.update(context.context.time.dt);

    if (context.context.distanceToCurrentPlayer < 10.0f && !m_attacked)
    {
        auto damageEvent           = std::make_unique<EntityDamageEvent>(context.context.id);
        damageEvent->target        = context.context.currentPlayerID;
        damageEvent->source.amount = 5;
        context.events.emit(std::move(damageEvent));

        m_attacked = true;
    }

    if (context.context.distanceToCurrentPlayer > 100.0f)
    {
        return WuskkogelStateID::Follow;
    }

    return WuskkogelStateID::Attack;
}
