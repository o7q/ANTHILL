#pragma once

#include "entity/body/entity_body.hpp"
#include "entity/update_context.hpp"
#include "math/rectangle.hpp"
#include "math/vec.hpp"

class BodyUpdateHandler
{
  public:
    BodyUpdateHandler(EntityBody &body, const StaticGridRectangle &boundingBox)
        : r_body(body), r_boundingBox(boundingBox)
    {
    }
    virtual ~BodyUpdateHandler() = default;

    void update(const EntityUpdateContext &context);

  private:
    void apply_external_forces(Vec2i startPos,
                               const EntityUpdateContext &context);
    void prevent_world_collision(Vec2f startPos, Vec2f updatedPos,
                                 const EntityUpdateContext &context);

  private:
    EntityBody &r_body;
    const StaticGridRectangle &r_boundingBox;
};
