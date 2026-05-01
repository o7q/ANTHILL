#pragma once

#include "assets/assets.hpp"
#include "backend/timer/timer.hpp"
#include "entities/simple_projectile/simple_projectile.hpp"
#include "events/backend/events.hpp"
#include "events/entity/events.hpp"
#include "identifiers/assets/sounds.hpp"
#include "identifiers/assets/spritesheet.hpp"
#include "item/context.hpp"
#include "item/renderable.hpp"
#include "items/weapons/gun.hpp"
#include "math/angle.hpp"
#include "math/random.hpp"
#include "sprite/sprite_animator.hpp"
#include <memory>

class Shotgun : public Gun, public IRenderable
{
  public:
    Shotgun(const Assets &assets)
        : Gun("Shotgun"), m_animator(assets.spriteSheets().get(SpriteSheetID::Item_Shotgun))
    {
        m_fireMode = FireMode::SemiAuto;

        m_muzzlePosition = {17, 7};

        setMagazineSize(10);
        m_fireCooldownTimer.setDurationInSeconds(0.25f);

        addAmmo(200);

        m_animator.setFPS(20);
        m_animator.disableLooping();
        m_fireCooldownTimer.restart();
    }

    virtual void update(float dt) override
    {
        m_fireCooldownTimer.update(dt);
        m_animator.update(dt);
    }

    virtual bool use(const ItemUseContext &context, EventPool<EntityEvent> &eventsOut) override
    {
        if (m_fireCooldownTimer.completed() && getAmmoInMagazine() > 0)
        {
            fire(context, eventsOut);
            m_fireCooldownTimer.restart();
            m_animator.restart();

            auto shootSoundEvent = std::make_unique<BackendPlaySoundEvent>();

            constexpr SoundID sounds[3] = {SoundID::WeaponShotgunFire1, SoundID::WeaponShotgunFire2,
                                           SoundID::WeaponShotgunFire3};

            shootSoundEvent->soundID         = sounds[Math::Random::unseededRandomInt(0, 3)];
            shootSoundEvent->settings.volume = 0.2f;
            shootSoundEvent->settings.pitch  = 100.0f / Math::Random::unseededRandomInt(95, 100);

            eventsOut.emit(std::make_unique<EntityBackendEvent>(context.ownerID, std::move(shootSoundEvent)));

            return true;
        }

        return false;
    }

    const Texture *getTexture() const override { return m_animator.getCurrentFrame(); }

    bool reload(const ItemUseContext &context, EventPool<EntityEvent> &eventsOut) override
    {
        if (restock_ammo())
        {
            auto reloadSoundEvent             = std::make_unique<BackendPlaySoundEvent>();
            reloadSoundEvent->soundID         = SoundID::WeaponShotgunReload1;
            reloadSoundEvent->settings.volume = 0.2f;
            reloadSoundEvent->settings.pitch  = 100.0f / Math::Random::unseededRandomInt(95, 100);

            eventsOut.emit(
                std::make_unique<EntityBackendEvent>(context.ownerID, std::move(reloadSoundEvent)));

            return true;
        }

        return false;
    }

  protected:
    virtual void fire(const ItemUseContext &context, EventPool<EntityEvent> &eventsOut) override
    {
        float radians = Degrees(context.heldAngle).radians();

        Vec2f n = {std::cosf(radians), std::sinf(radians)};
        n *= 8;

        for (int i = -3; i <= 3; ++i)
        {
            auto event = std::make_unique<EntitySpawnEvent>(context.ownerID);

            auto bullet = std::make_unique<SimpleProjectile>(
                context.ownerID, context.heldPosition + n.toGrid(), radians + i / 15.0f, 30.0f);

            event->entity = std::move(bullet);

            eventsOut.emit(std::move(event));
        }

        depleteAmmo();
    }

  private:
    Timer m_fireCooldownTimer;
    SpriteAnimator m_animator;
};
