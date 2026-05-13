#pragma once

#include "core/math/vec.hpp"
#include "entity/body/entity_body.hpp"
#include "entity/collider/entity_collider.hpp"
#include "entity/update_context.hpp"

class BodyUpdateHandler
{
  public:
    BodyUpdateHandler(EntityBody &body, const EntityCollider &collider) : r_body(body), r_collider(collider)
    {
    }
    virtual ~BodyUpdateHandler() = default;

    void update(const EntityUpdateContext &context);

  private:
    void apply_external_forces(Vec2i startPos, const EntityUpdateContext &context);
    void prevent_world_collision(Vec2f startPos, Vec2f updatedPos, const EntityUpdateContext &context);

  private:
    EntityBody &r_body;
    const EntityCollider &r_collider;
};
