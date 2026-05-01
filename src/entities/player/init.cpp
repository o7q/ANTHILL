#include "items/weapons/shotgun.hpp"
#include "player.hpp"

Player::Player(uint64_t id, InputHandler &input, const Assets &assets)
    : Entity(id), r_input(input), r_assets(assets), m_bodyHandler(m_body, m_boundingBox), m_sprite(assets)
{
    m_boundingBox.setSize({3, 21});
    m_metadata.type = EntityType::Player;

    auto shotgun = std::make_unique<Shotgun>(assets);
    m_inventory.addItem(std::move(shotgun), 0);

    m_metadata.name = "Player";
}
