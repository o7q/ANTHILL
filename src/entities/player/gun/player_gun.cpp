#include "player_gun.hpp"

#include "core/math/random.hpp"
#include "entities/player_projectile/player_projectile.hpp"
#include "events/entity/events.hpp"
#include "events/external/events.hpp"

PlayerGun::PlayerGun()
{
    m_shootCooldown.setDurationInSeconds(0.15f);
    m_shootCooldown.restart();
}

void PlayerGun::update(float dt) { m_shootCooldown.update(dt); }

void PlayerGun::shoot(Vec2i pos, Angle aimPos, uint64_t id, EventPool<EntityEvent> &eventsOut)
{
    if (m_shootCooldown.completed())
    {
        auto projectile           = std::make_unique<PlayerProjectile>(id, pos, aimPos, 20.0f);
        auto projectileSpawnEvent = std::make_unique<EntitySpawnEvent>(id, std::move(projectile));
        eventsOut.emit(std::move(projectileSpawnEvent));

        auto soundEvent             = std::make_unique<ExternalPlaySoundEvent>();
        soundEvent->soundID         = SoundID::SumiGunShoot1;
        soundEvent->settings.volume = 0.3f;
        soundEvent->settings.pitch  = Math::Random::unseededRandomInt(95, 100) / 100.0f;
        eventsOut.emit(std::make_unique<EntityExternalEvent>(id, std::move(soundEvent)));

        m_shootCooldown.restart();
    }
}
