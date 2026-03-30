#pragma once

#include "assets/assets.hpp"
#include "backend/input/input_handler.hpp"
#include "backend/viewport/viewport.hpp"
#include "entity/entity.hpp"
#include "entity/interfaces/head.hpp"
#include "entity/metadata.hpp"
#include "entity/modules/jump_handler/jump_handler.hpp"
#include "events/entity/entity_entity.hpp"
#include "item/inventory.hpp"
#include "items/weapons/pistol.hpp"
#include "math/angle.hpp"
#include "world/camera/camera.hpp"
#include <memory>

class Player : public Entity, public IHead
{
  public:
    Player(uint64_t id, InputHandler &input, const Assets &assets)
        : Entity(id), r_input(input), r_assets(assets)
    {
        m_interactionBox.getBoundingBox().setSize({10, 25});
        m_body.setGravity(0.4f);
        m_metadata.faction = EntityFaction::Player;

        auto pistol = std::make_unique<Pistol>();
        m_inventory.addItem(std::move(pistol), 0);

        m_metadata.name = "Player";
    }
    virtual ~Player() = default;

    Inventory &getInventory() { return m_inventory; }

    virtual void update(const EntityUpdateContext &context) override;

    void render(Viewport &viewport, const Camera &camera) override
    {
        viewport.drawTexture(
            *r_assets.textures().get(TextureID::Character),
            camera.worldToViewport(m_body.getPosition(), viewport));
        renderDebug_boundingBox(viewport, camera, Color(79, 255, 94));
    }

    void updateAimPosition(Vec2i aimPos)
    {
        m_angle = Math::Angle::vectorsToAngle(m_body.getPosition().toFloat(),
                                              aimPos.toFloat());
    }

  private:
    InputHandler &r_input;
    const Assets &r_assets;
    JumpHandler m_jumpHandler;
    Inventory m_inventory;

    Vec2i m_mouseWorldPos;
};
