#pragma once

#include "assets/assets.hpp"
#include "backend/timer/timer.hpp"
#include "entities/simple_projectile/simple_projectile.hpp"
#include "events/entity/entity_entity.hpp"
#include "identifiers/assets/spritesheet.hpp"
#include "item/context.hpp"
#include "item/renderable.hpp"
#include "items/weapons/gun.hpp"
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
    }

    virtual void update(float dt) override
    {
        m_fireCooldownTimer.update(dt);
        m_animator.update(dt);
    }

    virtual void use(const ItemUseContext &context,
                     EventPool<EntityEvent> &eventsOut) override
    {
        if (m_fireCooldownTimer.completed() && getAmmoInMagazine() > 0)
        {
            fire(context, eventsOut);
            m_fireCooldownTimer.restart();
            m_animator.restart();
        }
    }

    const Texture *getTexture() const override
    {
        return m_animator.getCurrentFrame();
    }

  protected:
    virtual void fire(const ItemUseContext &context,
                      EventPool<EntityEvent> &eventsOut) override
    {
        Vec2f n = {std::cosf(context.heldAngle), std::sinf(context.heldAngle)};
        n *= 8;

        for (int i = -1; i <= 1; ++i)
        {
            auto event = std::make_unique<EntitySpawnEvent>(context.ownerID);

            event->entityFactory = [i, context, n](uint64_t id)
            {
                auto bullet = std::make_unique<SimpleProjectile>(
                    id, context.ownerID, context.heldPosition + n.toGrid(),
                    context.heldAngle + i / 10.0f, 30.0f);

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
