#pragma once

#include "assets/assets.hpp"
#include "backend/timer/timer.hpp"
#include "entities/simple_projectile/simple_projectile.hpp"
#include "events/entity/base.hpp"
#include "events/entity/events.hpp"
#include "events/event_pool.hpp"
#include "identifiers/assets/spritesheet.hpp"
#include "item/context.hpp"
#include "items/weapons/gun/gun.hpp"
#include "math/angle.hpp"
#include "sprite/sprite_animator.hpp"
#include <memory>

class Shotgun : public Gun
{
  public:
    Shotgun(const Assets &assets)
        : Gun("Shotgun"), m_animator(assets.spriteSheets().get(SpriteSheetID::Item_Shotgun))
    {
        m_fireMode = FireMode::SemiAuto;

        m_relativeMuzzlePosition = {17, 7};

        addAmmo(200);
        setMagazineSize(10);

        m_fireCooldownTimer.setDurationInSeconds(0.25f);

        m_animator.setFPS(20);
        m_animator.disableLooping();
        m_fireCooldownTimer.restart();
    }

    virtual void update(float dt) override
    {
        m_fireCooldownTimer.update(dt);
        m_animator.update(dt);
    }

    virtual void use(const ItemUseContext &context, EventPool<EntityEvent> &eventsOut) override
    {
        if (m_fireCooldownTimer.completed() && getAmmoInMagazine() > 0)
        {
            fire(context, eventsOut);
            m_fireCooldownTimer.restart();
            m_animator.restart();
        }
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

        depleteAmmo(1);
    }

  private:
    Timer m_fireCooldownTimer;
    SpriteAnimator m_animator;
};
