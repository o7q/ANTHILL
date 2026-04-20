#pragma once

#include "assets/assets.hpp"
#include "backend/input/input_handler.hpp"
#include "backend/viewport/render_command.hpp"
#include "entity/body_update_handler/body_update_handler.hpp"
#include "entity/entity.hpp"
#include "entity/jump_handler/jump_handler.hpp"
#include "entity/metadata.hpp"
#include "events/entity/entity_entity.hpp"
#include "identifiers/assets/spritesheet.hpp"
#include "item/inventory.hpp"
#include "items/weapons/shotgun.hpp"
#include "math/angle.hpp"
#include "sprite/sprite_animator.hpp"
#include "sprite/sprite_system.hpp"
#include <memory>
#include <unordered_map>

class Player : public Entity
{
  public:
    Player(uint64_t id, InputHandler &input, const Assets &assets);
    virtual ~Player() = default;

    Inventory &getInventory() { return m_inventory; }

    void update(const EntityWorldContext &worldContext,
                EventPool<EntityEvent> &eventsOut) override;

    void render(const Camera &camera,
                std::vector<RenderCommand> &commandsOut) override;

    void updateAimPosition(Vec2i aimPos)
    {
        m_angle = Math::Angles::vectorsToAngle(m_body.getPosition().toFloat(),
                                               aimPos.toFloat())
                      .degrees();
    }

  private:
    InputHandler &r_input;
    const Assets &r_assets;
    BodyUpdateHandler m_bodyHandler;
    JumpHandler m_jumpHandler;
    Inventory m_inventory;

    Vec2i m_mouseWorldPos;

    float m_angle = 0.0f;

    SpriteSystem m_sprite;
};
