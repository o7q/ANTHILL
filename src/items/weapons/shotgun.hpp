#pragma once

#include "assets/assets.hpp"
#include "backend/timer/timer.hpp"
#include "entities/simple_projectile/simple_projectile.hpp"
#include "events/entity/entity_entity.hpp"
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
        : Gun("Shotgun"),
          m_animator(*assets.spriteSheets().get(SpriteSheetID::Shotgun))
    {
        m_fireMode = FireMode::SemiAuto;

        m_muzzlePosition = {17, 7};
        m_gripPoint1 = {3, 3};
        m_gripPoint2 = {9, 3};

        setMagazineSize(10);
        m_fireCooldownTimer.setDurationInSeconds(0.25f);

        addAmmo(200);

        m_animator.setFPS(20);
        m_fireCooldownTimer.restart();
    }

    virtual void update(float dt) override
    {
        m_fireCooldownTimer.update(dt);
        m_animator.update(dt);
    }

    virtual bool use(const ItemUseContext &context,
                     EventPool<EntityEvent> &eventsOut) override
    {
        if (m_fireCooldownTimer.completed() && getAmmoInMagazine() > 0)
        {
            fire(context, eventsOut);
            m_fireCooldownTimer.restart();
            m_animator.restart();
            return true;
        }

        return false;
    }

    const Texture *getTexture() const override
    {
        return m_animator.getCurrentFrame();
    }

    const SoundIDKey getUseSound() const override
    {
        constexpr SoundID sounds[3] = {SoundID::WeaponShotgunFire1,
                                       SoundID::WeaponShotgunFire2,
                                       SoundID::WeaponShotgunFire3};

        return sounds[Math::Random::weakRandInt(0, 3)];
    }

    const SoundIDKey getReloadSound() const override
    {
        return SoundID::WeaponShotgunReload1;
    }

  protected:
    virtual void fire(const ItemUseContext &context,
                      EventPool<EntityEvent> &eventsOut) override
    {
        float radians = Degrees(context.heldAngle).radians();

        Vec2f n = {std::cosf(radians), std::sinf(radians)};
        n *= 8;

        for (int i = -3; i <= 3; ++i)
        {
            auto event = std::make_unique<EntitySpawnEvent>(context.ownerID);

            event->entityFactory = [i, context, n, radians](uint64_t id)
            {
                auto bullet = std::make_unique<SimpleProjectile>(
                    id, context.ownerID, context.heldPosition + n.toGrid(),
                    radians + i / 15.0f, 30.0f);

                return bullet;
            };

            eventsOut.emit(std::move(event));
        }

        depleteAmmo();
    }

  private:
    Timer m_fireCooldownTimer;
    SpriteAnimator m_animator;
};
