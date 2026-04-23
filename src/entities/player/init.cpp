#include "items/weapons/shotgun.hpp"
#include "player.hpp"

Player::Player(uint64_t id, InputHandler &input, const Assets &assets)
    : Entity(id), r_input(input), r_assets(assets),
      m_bodyHandler(m_body, m_boundingBox)
{
    m_boundingBox.setSize({7, 22});
    m_metadata.type = EntityType::Player;

    auto shotgun = std::make_unique<Shotgun>(assets);
    m_inventory.addItem(std::move(shotgun), 0);

    m_metadata.name = "Player";

    SpriteAnimator run(
        *assets.spriteSheets().get(SpriteSheetID::Entity_SumiRun));
    run.setFPS(12);
    m_sprite.addAnimator(run, "run");

    SpriteAnimator idle(
        *assets.spriteSheets().get(SpriteSheetID::Entity_SumiIdle));
    idle.setFPS(5);
    m_sprite.addAnimator(idle, "idle");

    SpriteAnimator idleToRun(
        *assets.spriteSheets().get(SpriteSheetID::Entity_SumiIdleToRun));
    idleToRun.setFPS(10);
    m_sprite.addAnimator(idleToRun, "idleToRun");

    m_sprite.switchAnimator("idle");
}
