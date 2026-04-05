#pragma once

#include "assets/assets.hpp"
#include "backend/input/input_handler.hpp"
#include "backend/viewport/render_command.hpp"
#include "entity/body_update_handler/body_update_handler.hpp"
#include "entity/entity.hpp"
#include "entity/jump_handler/jump_handler.hpp"
#include "entity/metadata.hpp"
#include "events/entity/entity_entity.hpp"
#include "item/inventory.hpp"
#include "items/weapons/shotgun.hpp"
#include "math/angle.hpp"
#include <memory>

class Player : public Entity
{
  public:
    Player(uint64_t id, InputHandler &input, const Assets &assets)
        : Entity(id), r_input(input), r_assets(assets),
          m_bodyHandler(m_body, m_boundingBox)
    {
        m_boundingBox.setSize({10, 25});
        m_metadata.faction = EntityFaction::Player;

        auto shotgun = std::make_unique<Shotgun>(assets);
        m_inventory.addItem(std::move(shotgun), 0);

        m_metadata.name = "Player";
    }
    virtual ~Player() = default;

    Inventory &getInventory() { return m_inventory; }

    void update(const EntityUpdateContext &context,
                EventPool<EntityEvent> &eventsOut) override;

    void render(const Camera &camera,
                std::vector<RenderCommand> &commandsOut) override;
    void renderBox(const Camera &camera,
                   std::vector<RenderCommand> &commandsOut);

    void updateAimPosition(Vec2i aimPos)
    {
        m_angle = Math::Angle::vectorsToAngle(m_body.getPosition().toFloat(),
                                              aimPos.toFloat());
    }

  private:
    InputHandler &r_input;
    const Assets &r_assets;
    BodyUpdateHandler m_bodyHandler;
    JumpHandler m_jumpHandler;
    Inventory m_inventory;

    Vec2i m_mouseWorldPos;

    float m_angle = 0.0f;
};
