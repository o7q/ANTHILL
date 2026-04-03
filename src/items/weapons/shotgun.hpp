#pragma once

#include "entities/simple_projectile/simple_projectile.hpp"
#include "events/entity/entity_entity.hpp"
#include "item/owner_context.hpp"
#include "items/weapons/gun.hpp"
#include <memory>

class Shotgun : public Gun
{
  public:
    Shotgun() : Gun("Shotgun") { m_fireMode = FireMode::SemiAuto; }

  protected:
    virtual void fire(const ItemOwnerContext &ownerContext) override
    {
        for (int i = -1; i <= 1; ++i)
        {
            auto event = std::make_unique<EntitySpawnEvent>(ownerContext.id);

            event->entityFactory = [i, ownerContext](uint64_t id)
            {
                auto bullet = std::make_unique<SimpleProjectile>(
                    id, ownerContext.id, ownerContext.pos,
                    ownerContext.angle + i / 10.0f, 30.0f);

                return bullet;
            };

            ownerContext.eventEmitter.emit(std::move(event));
        }
    }

  private:
};
