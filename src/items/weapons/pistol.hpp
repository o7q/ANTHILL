#pragma once

#include "entities/projectile/projectile.hpp"
#include "events/entity/entity_entity.hpp"
#include "item/owner_context.hpp"
#include "items/weapons/gun.hpp"
#include <memory>

class Pistol : public Gun
{
  public:
    Pistol() : Gun("Pistol") { m_fireMode = FireMode::SemiAuto; }

  protected:
    virtual void fire(const ItemOwnerContext &ownerContext) override
    {
        auto event = std::make_unique<EntitySpawnEvent>(ownerContext.id);

        event->entityFactory = [ownerContext](uint64_t id)
        {
            auto bullet = std::make_unique<Projectile>(
                id, ownerContext.id, ownerContext.pos, ownerContext.angle);

            return bullet;
        };

        ownerContext.eventEmitter.emit(std::move(event));
    }

  private:
};
